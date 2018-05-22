#include "BlockManager.h"
#include <array>
#include <iostream>
#include "GameConfig.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "MouseInput.h"
#include "GameManager.h"



BlockManager::BlockManager(DifficultyAssister* difficultyAssister) : m_difficultyAssister(difficultyAssister)
{
	//Instanciate block pool with the size the board.
	m_blockPool = new BlockPool(COLS * ROWS);
	//Initialize blocks array and vector
	std::array<std::array<Block*, COLS>, ROWS> m_blocks = std::array<std::array<Block*, COLS>, ROWS>(); 
	std::vector<Block*> m_deletedBlocks = std::vector<Block*>();

	//Load all the textures
	m_blueTex = ResourceManager::LoadTexture("Content/blue.png");
	m_redTex = ResourceManager::LoadTexture("Content/red.png");
	m_greenTex = ResourceManager::LoadTexture("Content/green.png");
	m_purpleTex = ResourceManager::LoadTexture("Content/purple.png");
	m_yellowTex = ResourceManager::LoadTexture("Content/yellow.png");
	m_greyTex = ResourceManager::LoadTexture("Content/grey.png");
	m_bomb = ResourceManager::LoadTexture("Content/bomb.png");
	m_sword = ResourceManager::LoadTexture("Content/sword.png");
	m_lightning = ResourceManager::LoadTexture("Content/lightning.png");
		
	//Load Sounds
	m_clickSound = ResourceManager::LoadSound("Content/click.wav");
	m_bombSound = ResourceManager::LoadSound("Content/bomb.wav");
	m_lightningSound = ResourceManager::LoadSound("Content/lightning.wav");
	m_swordSound = ResourceManager::LoadSound("Content/sword.wav");

	//Set all blocks to null
	for(auto row : m_blocks)
	{
		for(auto block : row)
		{
			block = nullptr;
		}
	}

	//Initialize highlight object
	m_highlight = new GameObject();
	m_highlight->LoadTexture("Content/highlight.png");
		
	m_isGameLost = false;

	//Random numbers generation
	std::random_device rd;
	generator = std::default_random_engine(rd());
	distribution = std::uniform_real_distribution<float>(-1, 1);
	randNum = std::bind(distribution, generator);

}

BlockManager::~BlockManager()
{
	m_difficultyAssister = nullptr;
	delete m_blockPool;
	m_blockPool = nullptr;

	//delete block in board
	for(auto row : m_blocks)
	{
		for(auto block : row)
		{
			delete block;
			block = nullptr;
		}
	}	

	//Delete blocks in delelted blocks vector
	for(auto block : m_deletedBlocks)
	{
		delete block;
		block = nullptr;		
	}
	m_deletedBlocks.clear();

	SDL_DestroyTexture(m_highlight->GetTexture());
	delete(m_highlight);
	m_highlight = nullptr;

	SDL_DestroyTexture(m_blueTex);
	SDL_DestroyTexture(m_redTex);
	SDL_DestroyTexture(m_greenTex);
	SDL_DestroyTexture(m_purpleTex);
	SDL_DestroyTexture(m_yellowTex);
	SDL_DestroyTexture(m_greyTex);
	SDL_DestroyTexture(m_lightning);
	SDL_DestroyTexture(m_bomb);
	SDL_DestroyTexture(m_sword);
	
	m_blueTex = nullptr;
	m_redTex = nullptr;
	m_greenTex = nullptr;
	m_purpleTex = nullptr;
	m_yellowTex = nullptr;
	m_greyTex = nullptr;
	m_lightning = nullptr;	
	m_bomb = nullptr;
	m_sword = nullptr;

	Mix_FreeChunk(m_clickSound);
	m_clickSound = nullptr;
	Mix_FreeChunk(m_bombSound);
	m_bombSound = nullptr;
	Mix_FreeChunk(m_lightningSound);
	m_lightningSound = nullptr;
	Mix_FreeChunk(m_swordSound);
	m_swordSound = nullptr;

}

/// <summary>
/// Runs every tick and updates all the necessary logic for the blocks. 
/// Calculates the cooldown for the mouse clicks after succefully clicking a block.
/// Updates the board when needed. 
/// Highlights the block hovered by the mouse and checks for mouse clicks
/// </summary>
void BlockManager::Update(float deltaTime)
{	 
	//Get mouse position as indexes values of the matrix
	Vector2 vector = CalculateClickedBlockIndex();
	//If index is in bounds and the game is not lost
	if(IsIndexInBounds(vector.X, vector.Y) && !m_isGameLost)
	{
		//Set the highligh in the block if there is one at that position
		if(m_blocks[vector.X][vector.Y] != nullptr)
		{
			m_highlight->SetVisibility(true);
			m_highlight->SetPosition(GetPos(vector.X, vector.Y));
		}

		//If left mouse button clicked and the player can click
		if(MouseInput::IsLeftButtonDown() && m_canClick)
		{			
			//Click in a block
			if(ClickBlock(vector.X, vector.Y, false))
			{
				m_canClick = false;
				m_clickTimer = 0;
				Mix_PlayChannel(-1, m_clickSound, 0);
				//When the player can click again the blocks positions also update
				MoveTopBlockDown();

			}
		}
	}
	else
	{
		//If highlight is visible set it to false
		if(m_highlight->IsVisible())
			m_highlight->SetVisibility(false);
	}
	
	//After successfully clicking a block the player has to wait
	m_clickTimer += deltaTime;
	if(m_clickTimer > m_clickCooldown)
	{		
		m_canClick = true;
		
		//If click successfull check for empty lines and updates them
		CheckForEmptyCols();
	}
		
	//Updates all the blocks
	for(auto row : m_blocks)
	{
		for(auto block : row)
		{
			if(block != nullptr)
			{
				block->Update(deltaTime);
			}
		}			
	}
	
	//Loops through the deleted blocks and updates the animations
	const int size = m_deletedBlocks.size();	
	for(int i = size - 1; i > -1; i--)
	{
		m_deletedBlocks[i]->Update(deltaTime);
		//When a block is offscreen places it back in the pool
		if(m_deletedBlocks[i]->IsOffScreen())
		{
			m_blockPool->ReturnBlock(m_deletedBlocks[i]);
			m_deletedBlocks.erase(m_deletedBlocks.begin() + i);
		}
	}
}

/// <summary>
/// Calls the render method for all the blocks and the highlight box.
/// </summary>
void BlockManager::Render()
{
	for(auto row : m_blocks)
	{
		for(auto block : row)
		{
			if(block != nullptr)
			{				
				block->Render();
			}				
		}
	}
	m_highlight->Render();
	//Render Deleted blocks
	for(auto block : m_deletedBlocks)
	{
		block->Render();
	}
}

/// <summary>
/// Adds as Line of blocks to the end and push all the other blocks.	
/// Reverse loop, first pulls all the blocks then spawns the line at the start of the board.
/// Also checks if the game was lost when blocks are pushed out of the scope of the matrix.
/// </summary>
void BlockManager::AddLine()
{
	if(m_isGameLost)
		return;

	//Go through each coloumn
	for(int j = COLS - 1; j > -1; j--)
	{
		for(int i = 0; i  < ROWS; i++)
		{
		
			//If the bottom block is null -> continue to the next column		
			if(m_blocks[i][j] == nullptr && j != 0)
				break;
		
			//When there is a block
			if(m_blocks[i][j] != nullptr)
			{
				//If it is not out of scope
				if(j + 1 < COLS)
				{
					//Pushs this block backwards and leaves it black
					Vector2 pos = GetPos(i, j + 1);
					m_blocks[i][j]->SetPosition(pos);
					m_blocks[i][j + 1] = m_blocks[i][j];
					m_blocks[i][j] = nullptr;
				}
				else
				{
					//If blocks are push further than the scope of the matrix, the game was lost
					m_isGameLost = true;
					PopBlock(m_blocks[i][j]);
					m_blocks[i][j] = nullptr;
				}
			}
			//Spawns the new line
			if(j == 0)
			{
				m_blocks[i][j] = SpawnBlock(i, j);
			}
		}
		
	}
}

/// <summary>
/// Cleans the board and add 8 lines of blocks.
/// </summary>
void BlockManager::NewBoard()
{	
	m_canClick = false;
	m_clickTimer = 0;

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{			
			PopBlock(m_blocks[i][j]);
			m_blocks[i][j] = nullptr;
		}
	}

	//Adds 8 lines of blocks
	for(int i = 0; i < 8; i++)
	{
		AddLine();
	}
}

/// <summary>
/// Resets the game. Cleans the board, deletes the blocks falling (in the delete vector)
/// And returns blocks to pool. Creates a new board.
/// </summary>
void BlockManager::Reset()
{
	//When the game is reseted sets the game to not lost
	m_isGameLost = false;

	//Clean up the delete vector;
	const int size = m_deletedBlocks.size();	
	for(int i = size - 1; i > -1; i--)
	{
		m_blockPool->ReturnBlock(m_deletedBlocks[i]);	
		m_deletedBlocks.erase(m_deletedBlocks.begin() + i);
	}
	//Clean up he block currently in the board
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			//Return block to the pool
			m_blockPool->ReturnBlock(m_blocks[i][j]);
			m_blocks[i][j] = nullptr;
		}
	}

	//Get a new board
	NewBoard();
}

/// <summary>
/// Getter method to check is the game was lost.
/// Gets called by the GameManager.
/// </summary>
bool BlockManager::IsGameLost()
{
	return m_isGameLost;
}

/// <summary>
/// Called when a block is clicked. Checks if the neighbours have the same color or are a bomb or a sword
/// If yes the clicked block will be taped as well all the adjacent ones.
/// The blocks fall on top of each other when there are empty space below.
/// Recursive method, runs until all the neighbours with the same color are targeted. 	
/// </summary>
bool BlockManager::ClickBlock(int i, int j, bool hasNeighbours)
{	
	//If there is no block there -> return
	if(m_blocks[i][j] == nullptr)
		return false;
	
	BlockColor color = m_blocks[i][j]->GetColor();
	bool success = hasNeighbours;
	m_blocks[i][j]->SetClicked(true);

	//Check upper neighbour
	if(i + 1 < ROWS)
	{	
		Block* up = m_blocks[i + 1][j];
		if(up != nullptr && !up->WasClicked())
		{
			if(color == up->GetColor())
			{		
				success = true;
				ClickBlock(i + 1, j, true);
			}
		}
	}	
	//Check Down neighbour
	if(i - 1 >= 0)
	{
		Block* down = m_blocks[i - 1][j];
		if(down != nullptr && !down->WasClicked())
		{
			if(color == down->GetColor())
			{
				success = true;
				ClickBlock(i - 1, j, true);
			}
		}
	}
	//Check Left Neighbour
	if(j + 1 < COLS)
	{
		Block* left = m_blocks[i][j + 1];
		if(left != nullptr && !left->WasClicked())
		{			
			if(color == left->GetColor())
			{
				success = true;
				ClickBlock(i, j + 1, true);
			}			
		}		
	}
	//Check right neighbour
	if(j - 1 >= 0)
	{
		Block* right = m_blocks[i][j - 1];
		if(right != nullptr && !right->WasClicked())
		{
			if(color == right->GetColor())
			{
				success = true;
				ClickBlock(i, j - 1, true);
			}
		}
	}	
	if(success) // If success means that other blocks of the same color have been tapped
	{
		TapBlock(i, j);
		return true;
	}	
	m_blocks[i][j]->SetClicked(false);
	return false;
}

/// <summary>
/// Taps a block destroying it. If the block is of a special type call its special effect.
/// </summary>
/// <param name="i">Index in of the block the first array</param>
/// <param name="j">Index in of the block the second array</param>
void BlockManager::TapBlock(int i, int j)
{
	if(!IsIndexInBounds(i, j))
		return;

	Block* block = m_blocks[i][j];
	if(block == nullptr || block->IsTapped())
		return;
	
	//Prevents block from being tapped twice
	block->SetTapped(true);

	//Checks if this block is a power block with special effect, if yes, trigger it.
	switch(block->GetType())
	{
		case BlockType::Bomb:
			SetBomb(i, j);
			break;
		case BlockType::Lightning:
			SetLightning(i, j);
			break;
		case BlockType::Sword:
			SetSword(i, j);
			break;
	}	

	//Every successfull tap increases score
	GameManager::IncreaseScore();
	//Remove block from game
	PopBlock(block);
	m_blocks[i][j] = nullptr;
}

/// <summary>
/// Checks if the Index positions passed as params are in bounds.
/// </summary>
/// <returns>Returns false if the index is out of bounds.</returns>
bool BlockManager::IsIndexInBounds(int i, int j)
{
	if(j >= COLS)
	{
		return false;
	}
	else if(j < 0)
	{
		return false;
	}
	else if(i >= ROWS)
	{
		return false;
	}
	else if(i < 0)
	{
		return false;
	}
	return true;
}

/// <summary>
/// Spawns a new block at position i and j in the matrix.
/// Selects the block to be spawn.	
/// </summary>
/// <param name="i">Row index.</param>
/// <param name="j">Columns index.</param>
/// <returns>Pointer to the block created.</returns>
Block * BlockManager::SpawnBlock(int i, int j)
{
	Block* block = m_blockPool->SpawnBlock();
	SelectBlock(block);
	Vector2 pos = GetPos(i, j);
	block->SetPosition(pos);
	return block;
}

/// <summary>
/// Removes a block from the game board and places it into the delete vector.
/// Adds the block to the vector of deleted blocks to be animated.
/// Applies a force to the block, animating it
/// </summary>
void BlockManager::PopBlock(Block* block)
{	
	if(block != nullptr)
	{
		float x = randNum();
		//Give it an upwards push force
		block->ApplyForce(x * 2, -1);
		m_deletedBlocks.push_back(block);
	}
}


/// <summary>
/// Selects a random type of the texture for a block.
/// For normal blocks and lightning blocks, call the respective color method.
/// Uses the difficulty assister to retrive the color identifier value based on the progress of the game. 
/// </summary>
void BlockManager::SelectBlock(Block * block)
{
	int blockIdentifier = m_difficultyAssister->SelectBlockTypeValue();
	BlockType type;
	switch(blockIdentifier)
	{
		case 0:
			type = BlockType::Normal;
			SelectNormalColor(block);
			break;
		case 1:
			type = BlockType::Bomb;
			SelectPowerBlockColor(block);
			block->SetTexture(m_bomb);
			break;
		case 2:
			type = BlockType::Lightning;
			SelectPowerBlockColor(block);
			block->SetTexture(m_lightning);
			break;
		case 3:
			type = BlockType::Sword;
			SelectPowerBlockColor(block);
			block->SetTexture(m_sword);
			break;
		default:
			type = BlockType::Normal;
			break;
	}
	block->SetType(type);
}

/// <summary>
/// Selects a random color for a block and assigns the texture of that color.
/// Uses the difficulty assister to retrive the color identifier value based on the progress of the game. 
/// </summary>
/// <param name="block">Block to select the color for.</param>
void BlockManager::SelectNormalColor(Block * block)
{
	int colorNumber = m_difficultyAssister->SelectBlockColorValue();
	SDL_Texture* texture;
	BlockColor color; 
	switch(colorNumber)
	{
		case 0:
			color = BlockColor::Blue;
			texture = m_blueTex;
			break;
		case 1:
			color = BlockColor::Red;
			texture = m_redTex;
			break;
		case 2:
			color = BlockColor::Green;
			texture = m_greenTex;
			break;
		case 3:
			color = BlockColor::Purple;
			texture = m_purpleTex;
			break;
		case 4:
			color = BlockColor::Yellow;
			texture = m_yellowTex;
			break;		
		default:
			color = BlockColor::Grey;
			texture = m_greyTex;
			break;
	}
	block->SetColor(color);
	block->SetTexture(texture);
}

/// <summary>
/// Selects the color for the lightning texture and assigns the texture of that color. 
/// Uses the difficulty assister to retrive the color identifier value. 
/// </summary>
/// <param name="block">Block to choose the texture.</param>
void BlockManager::SelectPowerBlockColor(Block * block)
{
	int colorNumber = m_difficultyAssister->SelectBlockColorValue();
	BlockColor color;
	switch(colorNumber)
	{
		case 0:
			color = BlockColor::Blue;
			break;
		case 1:
			color = BlockColor::Red;
			break;
		case 2:
			color = BlockColor::Green;
			break;
		case 3:
			color = BlockColor::Purple;
			break;
		case 4:
			color = BlockColor::Yellow;
			break;
		default:
			color = BlockColor::Grey;
			break;
	}
	block->SetColor(color);
}

/// <summary>
/// Gets the X and Y world coordinates for a block in position i and j in the matrix.
/// </summary>
/// <param name="i">Index in the row that the block is.</param>
/// <param name="j">Index in the column that the block is.</param>
/// <returns>World position corresponding to the coordinates in the array </returns>
Vector2 BlockManager::GetPos(int i, int j)
{
	int x = GameConfig::SCREEN_WIDTH - (j + 1) * 32;
	int y = GameConfig::SCREEN_HEIGHT - (i+ 1) * 32 - FLOOR_HEIGHT;
	return Vector2(x,y);
}

/// <summary>
/// Calculates the position of the block that the mouse is hovering based on the mouse position.
/// </summary>
/// <returns>Returns a vector where the x and y are the indexes in the matrix.</returns>
Vector2 BlockManager::CalculateClickedBlockIndex()
{
	Vector2 mousePos = MouseInput::GetMousePosition();	
	int j = (-mousePos.X + GameConfig::SCREEN_WIDTH) / 32;
	int i = (GameConfig::SCREEN_HEIGHT - mousePos.Y - FLOOR_HEIGHT) / 32;
	return Vector2(i,j);
}


/// <summary>
/// For all the blocks in the matrix, checks if there is a block on top of it and moves the top blocks down. 
/// Recursive, will repeate for the positions on top of this one until the top row is reached.
/// </summary>
/// <param name="i">Index in the rows.</param>
/// <param name="j">Index in the coloumn.</param>
void BlockManager::MoveTopBlockDown()
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			//If block is there, theres no need to move others down in this column
			if(m_blocks[i][j] != nullptr)
				continue;

			int k = 1;	//Get the index of the next available block on top
			while(i + k < ROWS && (m_blocks[i + k][j] == nullptr || m_blocks[i + k][j]->WasClicked()))
			{
				k++;
			}

			if(i + k < ROWS)
			{
				//Replace the block with the new block
				m_blocks[i][j] = m_blocks[i + k][j];
				m_blocks[i + k][j] = nullptr;
				Vector2 pos = GetPos(i, j);
				//Trigger the block to fall down
				m_blocks[i][j]->TriggerFallDown(pos);
				
			}
			else if(i + k > ROWS )
			{
				//go to the next column
				break;
			}
		}
	}
}

/// <summary>
/// Checks if there is an empty line and pushes all the blocks back one row.
/// Firstly checks the bottom block to see if the line is empty.
/// Must be called after the blocks have been moved down. 
/// Checks one line at a time.
/// </summary>
void BlockManager::CheckForEmptyCols()
{
	for(int j = 0; j < COLS; j++)
	{	
		//Check first row, if it is empty, continue
		if(m_blocks[0][j] != nullptr)
		{
			continue;
			
		}		
		//If it goes out of scope break
		if(j + 1 >= COLS)
			break; 

		for(int i = 0; i < ROWS; i++)
		{				
			//If next block is empty ->Break
			if(m_blocks[i][j + 1] == nullptr)
				break;

			m_blocks[i][j] = m_blocks[i][j + 1];
			m_blocks[i][j + 1] = nullptr;
			Vector2 pos = GetPos(i, j);
			m_blocks[i][j]->SetPosition(pos);
		}		
	}
}

/// <summary>
/// Triggers a bomb at the position in the matrix passed as parameters.
/// A bomb will tap all the blocks in a radius of its position.
/// Bombs can make a chain with other power blocks.
/// </summary>
/// <param name="i">Index in first array</param>
/// <param name="j">Index in second array</param>
void BlockManager::SetBomb(int i, int j)
{	
	Mix_PlayChannel(-1, m_bombSound, 0);
	for(int k = 1; k < m_bombRadius + 1; k++)
	{	
			TapBlock(i + k, j);
			TapBlock(i + k, j);
			TapBlock(i - k, j);
			TapBlock(i, j+ k);
			TapBlock(i, j - k);
		
		if(k < m_bombRadius)
		{
			TapBlock(i + k, j + k);
			TapBlock(i - k, j - k);
			TapBlock(i - k, j + k);			
			TapBlock(i + k, j - k);
		}
	}
}

/// <summary>
/// Triggers a sword block at the position passed as parameters.
/// A sword will tap all the blocks in the same row and column
/// Swords can make a chain with other power blocks.
/// </summary>
/// <param name="i">Index in first array</param>
/// <param name="j">Index in second array</param>
void BlockManager::SetSword(int i, int j)
{
	Mix_PlayChannel(-1, m_swordSound, 0);
	for(int k = 0; k < COLS; k++)
	{
		TapBlock(i, k);
	}
	for(int k = 0; k < ROWS; k++)
	{
		TapBlock(k, j);
	}
}

/// <summary>
/// Triggers a lightning block at the position passed as parameters.
/// Lightning will tap all the blocks of the same color.
/// Swords can make a chain with other power blocks.
/// </summary>
/// <param name="i">Index in first array</param>
/// <param name="j">Index in second array</param>
void BlockManager::SetLightning(int i, int j)
{	
	Mix_PlayChannel(-1, m_lightningSound, 0);
	BlockColor color = m_blocks[i][j]->GetColor();
	for(int k = 0; k < ROWS; k++)
	{
		for(int l = 0; l < COLS; l++)
		{
			if(m_blocks[k][l] != nullptr && color == m_blocks[k][l]->GetColor())
			{
				TapBlock(k,l);				
			}
		}
	}
}

