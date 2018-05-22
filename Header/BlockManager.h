#pragma once
#include "Block.h"
#include "SDL_mixer.h"
#include <array>
#include "DifficultyAssister.h"
#include "BlockPool.h"

#ifndef BlockManager_h
#define BlockManager_h


/// <summary>
/// Manages all the blocks and interactions with the blocks. Spawns and destroys the blocks, updates the blocks positions when needed. 
/// Performs the power blocks logic.  
/// Checks when the game has been lost. 
/// </summary>
class BlockManager
{
public:
	BlockManager(DifficultyAssister* difficultyAssister);
	~BlockManager();
	void Update(float deltaTime); 
	void Render(); 
	void AddLine();
	void NewBoard();
	void Reset();
	bool IsGameLost();

private:
	/* CONSTANTS */ 	
	static const int FLOOR_HEIGHT = 128; //Height that blocks will be spawn 	
	static const int COLS = 20; //Number of max Columns
	static const int ROWS = 13; //Number of max rows 

	/* PRIVATE METHODS */	
	bool ClickBlock(int i, int j, bool neighboursChecked);	
	void TapBlock(int i, int j);
	bool IsIndexInBounds(int i, int j);
	
	Block* SpawnBlock(int i, int j);
	void PopBlock(Block* block);	
	void DeleteBlock(Block* block, int x, int y);
	void SelectBlock(Block* block);
	void SelectNormalColor(Block* block); 
	void SelectPowerBlockColor(Block* block);	
	Vector2 GetPos(int i, int j); 
	Vector2 CalculateClickedBlockIndex();
	void MoveTopBlockDown();
	void CheckForEmptyCols();
	void SetBomb(int i, int j);
	void SetSword(int i, int j);
	void SetLightning(int i, int j);

	/*PRIVATE FIELDS */
	DifficultyAssister* m_difficultyAssister; //Reference to the difficulty assister class.
	BlockPool* m_blockPool; //Pool of blocks.
	std::array<std::array<Block*, COLS>, ROWS> m_blocks; //Matrix containing all the active blocks.
	std::vector<Block*> m_deletedBlocks; //Contains all active blocks that are no longer in game but are still being animated.
	GameObject* m_highlight; //Highlight object on the blocks.
	
	SDL_Texture* m_blueTex = nullptr; //Texture of the blue box.
	SDL_Texture* m_redTex = nullptr; //Texture of the red box.
	SDL_Texture* m_greenTex = nullptr; //Texture of the gree box.
	SDL_Texture* m_purpleTex = nullptr; //Texture of the purple box.
	SDL_Texture* m_yellowTex = nullptr; //Texture of the yellow box.
	SDL_Texture* m_greyTex = nullptr; //Texture of the grey box.
	SDL_Texture* m_bomb = nullptr; //Texture of the bomb.
	SDL_Texture* m_lightning = nullptr; //Texture of the blue lightning	.
	SDL_Texture* m_sword = nullptr; //Texture of the sword.
	
	Mix_Chunk* m_clickSound = nullptr; //Click sound effect.
	Mix_Chunk* m_bombSound = nullptr; //Bomb sound effect.
	Mix_Chunk* m_lightningSound = nullptr; //Lightning sound effect.
	Mix_Chunk* m_swordSound = nullptr; //Sword sound effect.

	bool m_isGameLost; //When true the game is lost and it ends.
	bool m_canClick; //States if the player can click on the blocks.
	float m_clickTimer; //Timer to create a cooldown for the player click.
	float m_clickCooldown = 0.5; //Cooldown time after a mouse click.
	int m_bombRadius = 2; //Radius (in blocks) of the effect of the bomb.

	//Random Numbers Variables
	std::uniform_real_distribution<float> distribution; 
	std::default_random_engine generator;
	std::function<float()> randNum;

};

#endif