#include "GameManager.h"
#include "GameConfig.h"
#include "ResourceManager.h"
#include <string>

int GameManager::m_scoreMultiplier;

GameManager::GameManager()
{
	//Sets the first game state
	m_gameState = GameState::Menu;
	//Initialize Difficulty Assister
	m_difficultyAssister = new DifficultyAssister();
	//Initialize Block Manager
	m_blockManager = new BlockManager(m_difficultyAssister);
	
	//Set Game Stats	
	m_score = 0;
	m_experience = 0;
	m_scoreMultiplier = 0;
	m_timer = 0;
	m_pushTime = m_difficultyAssister->GetPushTime();
	m_nextLevel = m_difficultyAssister->GetNextLevelUp();
	m_level = 1;	
	m_textTimer = 0;
	m_scoreTimer = 0;
	m_updateScore = true;
	m_isMusicMute = false;
	m_isLoading = false;


	//Set the background texture	
	m_background = ResourceManager::LoadTexture("Content/background.png");

	//Set Background Music
	m_music = ResourceManager::LoadMusic("Content/music.wav");
	if(!m_isMusicMute)
		Mix_PlayMusic(m_music, -1);
	//Load Sound Effects
	m_levelUpSound = ResourceManager::LoadSound("Content/level_up.wav");
	m_gameOver = ResourceManager::LoadSound("Content/gameover.wav");
	m_buttonClick = ResourceManager::LoadSound("Content/button_click.wav");

	//Create and setup UI	
	m_timeSlider = new Slider();
	m_timeSlider->SetPosition(GameConfig::SCREEN_WIDTH * 0.5 + 200, 10);
	m_timeSlider->LoadTexture("Content/slider_back_1.png");
	m_timeSlider->SetFillTexture("Content/slider_fill_1.png");
	m_timeSlider->SetMaxValue(m_pushTime);

	m_experienceSlider = new Slider();
	m_experienceSlider->SetPosition(GameConfig::SCREEN_WIDTH * 0.5, 10);
	m_experienceSlider->LoadTexture("Content/slider_back_2.png");
	m_experienceSlider->SetFillTexture("Content/slider_fill_2.png");
	m_experienceSlider->SetMaxValue(m_nextLevel);	
	
	m_pauseButton = new Button();
	m_pauseButton->LoadTexture("Content/pause_button.png");
	m_pauseButton->LoadPressedTexture("Content/pause_button_pressed.png");
	m_pauseButton->LoadHoverTexture("Content/pause_button_hover.png");
	m_pauseButton->SetPosition(10, GameConfig::SCREEN_HEIGHT - 55);
	m_pauseButton->ToogleButton();

	m_muteButton = new Button();
	m_muteButton->LoadTexture("Content/mute_button.png");
	m_muteButton->LoadPressedTexture("Content/mute_button_pressed.png");
	m_muteButton->LoadHoverTexture("Content/mute_button_hover.png");
	m_muteButton->SetPosition(60, GameConfig::SCREEN_HEIGHT - 55);

	m_nextLineButton = new Button();
	m_nextLineButton->LoadTexture("Content/push.png");
	m_nextLineButton->SetPosition(GameConfig::SCREEN_WIDTH - 64, GameConfig::SCREEN_HEIGHT - 45);
	m_nextLineButton->LoadHoverTexture("Content/push_hover.png");
	
	m_nextLineButton = new Button();
	m_nextLineButton->LoadTexture("Content/push.png");
	m_nextLineButton->SetPosition(GameConfig::SCREEN_WIDTH - 64, GameConfig::SCREEN_HEIGHT - 45);
	m_nextLineButton->LoadHoverTexture("Content/push_hover.png");

	m_playButton = new Button();
	m_playButton->LoadTexture("Content/play.png");
	m_playButton->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_playButton->GetWidth() / 2, GameConfig::SCREEN_HEIGHT - 195);
	m_playButton->LoadHoverTexture("Content/play_hover.png");

	m_replayButton = new Button();
	m_replayButton->LoadTexture("Content/replay.png");
	m_replayButton->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_replayButton->GetWidth() / 2, GameConfig::SCREEN_HEIGHT /2);
	m_replayButton->LoadHoverTexture("Content/replay_hover.png");
	m_replayButton->SetVisibility(false);

	m_resumeButton = new Button();
	m_resumeButton->LoadTexture("Content/resume.png");
	m_resumeButton->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_replayButton->GetWidth() / 2, GameConfig::SCREEN_HEIGHT - 195);
	m_resumeButton->LoadHoverTexture("Content/resume_hover.png");
	m_resumeButton->SetVisibility(false);

	m_textBox = new Text();
	m_textBox->SetPosition(GameConfig::SCREEN_WIDTH / 2, 160);
	m_textBox->SetCenterOrigin(true);
	m_textBox->SetColor({ 56,56,56 });
	m_textBox->LoadFont("Content/font.ttf", 50);
	m_textBox->UpdateTextBox(m_levelupText);	
	m_textBox->SetVisibility(false);

	m_scoreBox = new Text();
	m_scoreBox->SetPosition(20, 16);
	m_scoreBox->SetColor({56, 56, 56});
	m_scoreBox->LoadFont("Content/font.ttf", 20);
	m_scoreBox->UpdateTextBox(("Score: " + std::to_string(m_score)).c_str());
	m_scoreBox->SetVisibility(true);

	m_levelText = new Text();
	m_levelText->SetPosition(250, 16);
	m_levelText->SetColor({ 56, 56, 56 });
	m_levelText->LoadFont("Content/font.ttf", 20);
	m_levelText->UpdateTextBox(("LEVEL: " + std::to_string(m_level)).c_str());
	m_levelText->SetVisibility(true);
	
	m_limit = new GameObject();
	m_limit->LoadTexture("Content/limit.png");
	m_limit->SetPosition(128 + m_limit->GetWidth()* 2 - m_limit->GetWidth()/2, 0);

	m_uiTopBox = new GameObject();
	m_uiTopBox->LoadTexture("Content/top_ui_back.png");
	
	m_uiBottomBox = new GameObject();
	m_uiBottomBox->LoadTexture("Content/bottom_ui_back.png");
	m_uiBottomBox->SetPosition(0, GameConfig::SCREEN_HEIGHT - 64);

	m_menu = new GameObject();
	m_menu->LoadTexture("Content/menu.png");
	m_menu->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_menu->GetWidth()/ 2, 100);

	m_blackScreen = new GameObject();
	m_blackScreen->LoadTexture("Content/black.png");
	m_blackScreen->SetPosition(-GameConfig::SCREEN_WIDTH, 0);
	m_blackScreen->SetScale(25,20);
	m_blackScreen->SetVisibility(false);

	m_floor = new GameObject();
	m_floor->LoadTexture("Content/floor.png");
	m_floor->SetPosition(0, GameConfig::SCREEN_HEIGHT - 128);

	m_tutorial1 = new GameObject();
	m_tutorial1->LoadTexture("Content/tutorial_1.png");
	m_tutorial1->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_menu->GetWidth() / 2, 100);
	m_tutorial1->SetVisibility(false);

	m_tutorial2 = new GameObject();
	m_tutorial2->LoadTexture("Content/tutorial_2.png");
	m_tutorial2->SetPosition(GameConfig::SCREEN_WIDTH / 2 - m_menu->GetWidth() / 2, 100);
	m_tutorial2->SetVisibility(false);

	//Setup background Animations
	planes = std::array<PlaneAnimation*, 3>();		
	planes[0] = new PlaneAnimation();
	planes[1] = new PlaneAnimation();
	planes[2] = new PlaneAnimation();

	clouds = std::array<GameObject*, 4>();
	clouds[0] = new GameObject();
	clouds[0]->SetPosition(0, 100);
	clouds[0]->LoadTexture("Content/cloud_1.png");
	clouds[1] = new GameObject();
	clouds[1]->SetPosition(GameConfig::SCREEN_WIDTH / 2, 100);
	clouds[1]->LoadTexture("Content/cloud_2.png");
	clouds[2] = new GameObject();
	clouds[2]->SetPosition(GameConfig::SCREEN_WIDTH, 100);
	clouds[2]->LoadTexture("Content/cloud_1.png");
	clouds[3] = new GameObject();
	clouds[3]->SetPosition(GameConfig::SCREEN_WIDTH + GameConfig::SCREEN_WIDTH /2, 100);
	clouds[3]->LoadTexture("Content/cloud_2.png");
}

GameManager::~GameManager()
{
	delete m_difficultyAssister;
	m_difficultyAssister = nullptr;
	delete(m_blockManager);
	m_blockManager = nullptr;
	//Clean Resources
	SDL_DestroyTexture(m_background);
	m_background = nullptr;
	Mix_FreeMusic(m_music);
	m_music = nullptr;
	Mix_FreeChunk(m_levelUpSound);
	m_levelUpSound = nullptr;
	Mix_FreeChunk(m_gameOver);
	m_gameOver = nullptr;
	Mix_FreeChunk(m_buttonClick);
	m_buttonClick = nullptr;


	//Clean UI
	delete m_timeSlider;
	m_timeSlider = nullptr;
	delete m_experienceSlider;
	m_experienceSlider = nullptr;
	delete m_pauseButton;
	m_pauseButton = nullptr;
	delete m_muteButton;
	m_muteButton = nullptr;
	delete m_nextLineButton;
	m_nextLineButton = nullptr;
	delete m_playButton;
	m_playButton = nullptr;
	delete m_replayButton;
	m_replayButton = nullptr;
	delete m_resumeButton;
	m_resumeButton = nullptr;
	
	delete m_textBox;
	m_textBox = nullptr;
	delete m_scoreBox;
	m_scoreBox = nullptr;
	delete m_levelText;
	m_levelText = nullptr;


	SDL_DestroyTexture(m_limit->GetTexture());
	delete(m_limit);
	m_limit = nullptr;
	SDL_DestroyTexture(m_uiTopBox->GetTexture());
	delete(m_uiTopBox);
	m_uiTopBox = nullptr;
	SDL_DestroyTexture(m_uiBottomBox->GetTexture());
	delete(m_uiBottomBox);
	m_uiBottomBox = nullptr;
	SDL_DestroyTexture(m_menu->GetTexture());
	delete(m_menu);
	m_menu = nullptr;
	SDL_DestroyTexture(m_blackScreen->GetTexture());
	delete(m_blackScreen);
	m_blackScreen = nullptr;
	SDL_DestroyTexture(m_tutorial1->GetTexture());
	delete(m_tutorial1);
	m_tutorial1 = nullptr;
	SDL_DestroyTexture(m_tutorial2->GetTexture());
	delete(m_tutorial2);
	m_tutorial2 = nullptr;


	//Delete Planes and clouds
	for(int i = 0; i <3; i++)
	{
		delete planes[i];
		planes[i] = nullptr;
	}	
	for(int i = 0; i <4; i++)
	{
		SDL_DestroyTexture(clouds[i]->GetTexture());
		delete clouds[i];
		clouds[i] = nullptr;
	}
}


void GameManager::Update(float deltaTime)
{
	//Updates the game depending on the current active state
	if(m_gameState == GameState::Running)
	{
		UpdateRunningState(deltaTime);
	}
	else if(m_gameState == GameState::Paused)
	{
		//If a transition is active
		if(m_isLoading)
		{
			//Set the blackscreen animation to move to the left
			if(UpdateBlackScreen(false))
			{
				m_isLoading = false;
				m_blackScreen->SetVisibility(false);
			}
			//While the transition is going  
			return;
		}
		m_resumeButton->Update(deltaTime);
		//Check if Buttons were clicked
		CheckPauseButton();
		CheckMuteButton();
	}
	else if(m_gameState == GameState::Ended)
	{
		UpdateEndedState(deltaTime);
	}
	else if(m_gameState == GameState::Menu)
	{
		UpdateMenuState(deltaTime);
	}

	//Updates the cloud and planes
	for(auto plane : planes)
	{
		plane->Update(deltaTime);
	
	}
	for(auto cloud : clouds)
	{
		//keep switching the cloud texture from one side to the other
		cloud->SetPosition(cloud->GetPosition().X - 1, cloud->GetPosition().Y);
		if(cloud->GetPosition().X < -400)
		{
			cloud->SetPosition(GameConfig::SCREEN_WIDTH + GameConfig::SCREEN_WIDTH /2 - 1, cloud->GetPosition().Y);
		}
	}
	
}

void GameManager::Render()
{
	//Always render the clouds
	for(auto cloud : clouds)
	{
		cloud->Render();
	}
	//Render background
	SDL_RenderCopy(Game::renderer, m_background, NULL, NULL);
	
	//Always render the planes
	for(auto plane : planes)
	{
		plane->Render();
	}
	
	//Render all game objects while GameState running, pause and ended
	if(m_gameState == GameState::Running || m_gameState == GameState::Paused || m_gameState == GameState::Ended)
	{		
		m_limit->Render();
		m_floor->Render();
		m_blockManager->Render();		
		m_uiTopBox->Render();
		m_uiBottomBox->Render();
		m_timeSlider->Render();
		m_experienceSlider->Render();
		m_pauseButton->Render();
		m_muteButton->Render();
		m_nextLineButton->Render();		
		m_textBox->Render();
		m_scoreBox->Render();
		m_levelText->Render();
		m_tutorial1->Render();
		m_tutorial2->Render();
		m_resumeButton->Render();
		if(m_updateScore) //Is not updated every frame for otmization
		{
			//update the score text box				
			m_scoreBox->UpdateTextBox(("Score: " + std::to_string(m_score)).c_str());			
			m_updateScore = false;
		}		
	}else if(m_gameState == GameState::Menu)
	{
		m_menu->Render();
		m_playButton->Render();
		m_replayButton->Render();
	}

	if(m_gameState == GameState::Ended)
	{
		m_replayButton->Render();
	}
	
	//Black screen is used to transition between states
	m_blackScreen->Render();

}

void GameManager::IncreaseScore()
{
	m_scoreMultiplier++;
}

void GameManager::LostFocus()
{
	//Pauses the game
	if(m_gameState == GameState::Running)
	{
		m_gameState = GameState::Paused;
	}
	//Stops the music when the window loses focus
	Mix_HaltMusic();
}

void GameManager::GainedFocus()
{
	//Resumes the game
	if(m_gameState == GameState::Paused)
	{
		m_gameState = GameState::Running;
	}
	//If the music is not music, resume play 
	if(!m_isMusicMute)
		Mix_PlayMusic(m_music, -1);
}

void GameManager::UpdateRunningState(float deltaTime)
{
	//If a transition is active
	if(m_isLoading)
	{
		//Set the blackscreen animation to move to the left
		if(UpdateBlackScreen(false))
		{
			m_isLoading = false;
			m_blackScreen->SetVisibility(false);
		}
		//While the transition is going  
		return;
	}

	//Timer to place new line 
	m_timer += deltaTime;
	if(m_timer >= m_pushTime)
	{
		m_blockManager->AddLine();
		m_timer = 0;
	}
	//Timer to check when it is time to update the score
	m_scoreTimer += deltaTime;
	if(m_scoreTimer >= 0.5)
	{
		m_updateScore = true;
		m_scoreTimer = 0;
	}

	//Updates Sliders Values
	m_timeSlider->SetCurrentValue(m_timer);
	m_experienceSlider->SetCurrentValue(m_experience);

	//Updates all objects
	m_blockManager->Update(deltaTime);
	m_timeSlider->Update(deltaTime);
	m_experienceSlider->Update(deltaTime);
	m_pauseButton->Update(deltaTime);
	m_muteButton->Update(deltaTime);
	m_nextLineButton->Update(deltaTime);
	

	//Check for level up
	if(m_experience > m_nextLevel)
	{
		LevelUp();
	}
	//Timer for level up message to be active
	if(m_textBox->IsVisible())
	{
		m_textTimer += deltaTime;
		if(m_textTimer > m_textTimeLenght)
		{
			m_textBox->SetVisibility(false);
			m_textTimer = 0;
		}
	}

	//Check if the game has been lost, transition to Game over state
	if(m_blockManager->IsGameLost())
	{
		m_menu->SetVisibility(true);
		m_replayButton->SetVisibility(true);
		m_textBox->UpdateTextBox(m_gameOverText);
		m_textBox->SetVisibility(true);
		m_gameState = GameState::Ended;

		Mix_PlayChannel(-1, m_gameOver, 0);
	}
	//Check button clicks
	CheckLineButton();
	CheckPauseButton();
	CheckMuteButton();
	//Updates the score based on this update tick
	UpdateScore();
}

void GameManager::UpdateEndedState(float deltaTime)
{
	m_replayButton->Update(deltaTime);
	//Still updates the block manager to display the block animations
	m_blockManager->Update(deltaTime);
	//Check if pause button was pressed
	if(m_replayButton->GotPressed())
	{
		Mix_PlayChannel(-1, m_buttonClick, 0);
		//Set the black screen on
		m_blackScreen->SetVisibility(true);
		m_isLoading = true;
		
	}
	//Transition to new game
	if(m_isLoading)
	{
		//When false the black screen has covered the whole screen
		if(UpdateBlackScreen(true))
		{
			m_menu->SetVisibility(false);
			m_replayButton->SetVisibility(false);
			ResetGame();
			m_gameState = GameState::Running;
		}
	}
}

void GameManager::UpdateMenuState(float deltaTime)
{
	m_playButton->Update(deltaTime);
	//Check if the play button has been pressed
	if(m_playButton->GotPressed())
	{
		//When pressed, set the black screen transition on
		Mix_PlayChannel(-1, m_buttonClick, 0);
		m_blackScreen->SetVisibility(true);
		m_isLoading = true;
	}
	
	if(m_isLoading)
	{
		//Updates the black screen 
		if(UpdateBlackScreen(true))
		{
			//When done -> transition to running state
			m_playButton->SetVisibility(false);
			m_menu->SetVisibility(false);
			m_blockManager->NewBoard();
			m_tutorial1->SetVisibility(true);
			m_resumeButton->SetVisibility(true);
			m_gameState = GameState::Paused;
		}
	}
}

void GameManager::UpdateScore()
{
	//Add the multiplier value square to the score and to the experience
	m_score += m_scoreMultiplier * m_scoreMultiplier;
	m_experience += m_scoreMultiplier * m_scoreMultiplier;
	//Resets the multiplier
	m_scoreMultiplier = 0;
}

void GameManager::ResetGame()
{
	//Reset Game Stats, the game board and the UI
	m_timer = 0;
	m_score = 0;
	m_experience = 0;
	m_level = 1;
	m_difficultyAssister->Reset();
	m_difficultyAssister->UpdateCurrentGameValues(1);
	m_pushTime = m_difficultyAssister->GetPushTime();
	m_nextLevel = m_difficultyAssister->GetNextLevelUp();
	m_blockManager->Reset();	
	m_timeSlider->SetMaxValue(m_pushTime);
	m_timeSlider->SetCurrentValue(0);
	m_experienceSlider->SetMaxValue(m_nextLevel);
	m_experienceSlider->SetCurrentValue(0);
	m_textBox->UpdateTextBox(m_levelupText);
	m_textBox->SetVisibility(false);
	m_levelText->UpdateTextBox(("LEVEL: " + std::to_string(m_level)).c_str());
	m_scoreBox->UpdateTextBox(("SCORE: " + std::to_string(m_score)).c_str());
}

void GameManager::CheckPauseButton()
{
	if(m_pauseButton->GotPressed())
	{
		//Play click button
		Mix_PlayChannel(-1, m_buttonClick, 0);
		//Toogle the game pause
		if(m_gameState == GameState::Paused)
		{
			//Remove text box pause message
			m_textBox->UpdateTextBox(m_levelupText);
			m_textBox->SetVisibility(false);
			m_tutorial1->SetVisibility(false);
			m_tutorial2->SetVisibility(false);
			m_resumeButton->SetVisibility(false);
			m_gameState = GameState::Running;
		}
		else if (m_gameState == GameState::Running)
		{
			//When paused -> displays a text box
			m_textBox->UpdateTextBox(m_pauseGameText);
			m_textBox->SetVisibility(true);
			m_resumeButton->SetVisibility(true);
			m_gameState = GameState::Paused;
		}
	}	

	if(m_resumeButton->GotPressed())
	{
		//Play click button
		Mix_PlayChannel(-1, m_buttonClick, 0);
		//Toogle the game pause
		if(m_gameState == GameState::Paused)
		{
			//Remove text box pause message
			m_textBox->UpdateTextBox(m_levelupText);
			m_textBox->SetVisibility(false);
			m_resumeButton->SetVisibility(false);
			m_gameState = GameState::Running;
			m_tutorial1->SetVisibility(false);
			m_tutorial2->SetVisibility(false);
			m_pauseButton->ToogleButton();

		}
	}
}

void GameManager::CheckMuteButton()
{	
	//Checks for button press
	if(m_muteButton->GotPressed())
	{
		//Toogles the music 
		Mix_PlayChannel(-1, m_buttonClick, 0);
		if(m_isMusicMute)
		{
			Mix_PlayMusic(m_music, -1);
			m_isMusicMute = false;
		}
		else
		{
			Mix_HaltMusic();
			m_isMusicMute = true;
		}
	}
}

void GameManager::CheckLineButton()
{
	//Calls the block manager when the add line button is pressed
	if(m_nextLineButton->GotPressed())
	{
		Mix_PlayChannel(-1, m_buttonClick, 0);
		m_nextLineButton->ToogleButton();
		m_blockManager->AddLine();
		//Resets the timer for the next line
		m_timer = 0;
	}
}

void GameManager::LevelUp()
{
	//Clears the board
	m_blockManager->NewBoard();
	m_level++;
	m_levelText->UpdateTextBox(("LEVEL: " + std::to_string(m_level)).c_str());
	//Update Difficulty of level Level
	m_difficultyAssister->UpdateCurrentGameValues(m_level);
	m_nextLevel = m_difficultyAssister->GetNextLevelUp();
	m_pushTime = m_difficultyAssister->GetPushTime();
	
	//Reset values
	m_experienceSlider->SetMaxValue(m_nextLevel);
	m_experience = 0;		
	m_timeSlider->SetMaxValue(m_pushTime);
	m_timer = 0;
	m_textBox->SetVisibility(true);

	//play level up sound
	Mix_PlayChannel(-1, m_levelUpSound, 0);
	//If the level needed to unlock power blocks is reached show the tutorial screen
	if(m_level == m_difficultyAssister->GetPowerBlockUnlockLevel())
	{
		//pause and game show tutorial message
		m_tutorial2->SetVisibility(true);
		m_textBox->UpdateTextBox(m_pauseGameText);
		m_textBox->SetVisibility(true);
		m_resumeButton->SetVisibility(true);
		m_gameState = GameState::Paused;
		
	}

}

bool GameManager::UpdateBlackScreen(bool enter)
{
	//If true -> screen moves to the right
	if(enter)
	{
		//Increments the current position of the black screen
		Vector2 pos = m_blackScreen->GetPosition();
		m_blackScreen->SetPosition(m_blackScreen->GetPosition() + Vector2(20, 0));
		//When if reach the end it return true
		if(m_blackScreen->GetPosition().X >= 0)
		{
			return true;
		}
	}
	else
	{
		//Decrements the current position of the black screen
		Vector2 pos = m_blackScreen->GetPosition();
		m_blackScreen->SetPosition(m_blackScreen->GetPosition() + Vector2(-20, 0));
		//When if reach the end it return true
		if(m_blackScreen->GetPosition().X <= -GameConfig::SCREEN_WIDTH)
		{
			return true;
		}
	}	
	return false;
}

