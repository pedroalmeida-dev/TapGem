#pragma once
#include "SDL_mixer.h"
#include "Button.h"
#include "Slider.h"
#include "BlockManager.h"
#include "DifficultyAssister.h"
#include "Text.h"
#include "PlaneAnimation.h"

#ifndef GameManager_h
#define GameManager_h

enum class GameState
{
	Menu, Running, Paused, Ended
};

/// <summary>
/// Root of the game itself. Instanciates all the gameObjects incluing UI and calls their update and render methods.
/// Keeps track of the game state and all the needed variables, pauses and unpauses the game. Sets the background and the animations. 
/// </summary>
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Update(float deltaTime); //Runs every tick
	void Render(); //Renders all the objects
	static void IncreaseScore(); //Increases the multiplier by one with each call 	
	void LostFocus(); //Gets called when the game window looses focus, pausing the game. 
	void GainedFocus(); //Gets called when the game window regains focus, resuming the game.
	

private:
	void UpdateRunningState(float deltaTime);//Updates the game when it is in the runnning state.
	void UpdateEndedState(float deltaTime); //Updates the game when it is in the ended state.
	void UpdateMenuState(float deltaTime);//Updates the game when it is in the menu state.
	void UpdateScore(); //Runs at the end of the update, updating the score in accordance to  the multiplier.
	void ResetGame(); //Resets all the variables and cleans the boards.
	void CheckPauseButton(); //Checks if the pause button has been press, and pauses and unpauses the game.
	void CheckMuteButton(); //Checks if the mute button has been pressed, and mutes/ unmutes the music.
	void CheckLineButton(); //Checks if the AddLine button has been pressed.
	void LevelUp(); //Updates all the variables and game when there is a level up.
	bool UpdateBlackScreen(bool enable); //Moves the black screen back and forth when it runs on update.

	GameState m_gameState; //Current Game state.
	DifficultyAssister* m_difficultyAssister; //Assists setting and updating the difficulty for the game.
	BlockManager* m_blockManager; //Takes care of all the blocks.
	
	int m_score;//Current score.
	int m_experience;//current experience.
	static int m_scoreMultiplier;//Is reseted every update. Used for each move.
	float m_timer; //Timer variable to check when it is time for the next push.
	float m_pushTime; //Current push interval.
	int m_nextLevel; //Current experience needed for the next level.
	
	int m_level;//Current level.
	float m_textTimer;//Timer used to control the level up text box.	
	float m_scoreTimer;//Used so that the text bo is not updated every frame.
	bool m_updateScore;//When true the score box updates thes score displayed.
	bool m_isMusicMute; //If true the music is mute.
	bool m_isLoading; //If true the black screen is on and a transition is currently active.
	const float m_textTimeLenght = 4; //Time that the level up text box lasts.


	SDL_Texture* m_background = nullptr; //Background texture.
	//Music and sound effects.
	Mix_Music* m_music = nullptr; //Reference the music.
	Mix_Chunk* m_levelUpSound = nullptr; //Level up sound effect.
	Mix_Chunk* m_gameOver = nullptr; //Sound effect for game over.
	Mix_Chunk* m_buttonClick = nullptr; //Sound effect for a button click.
	//UI Elements.
	Slider* m_timeSlider = nullptr; //Slider displaying the time for the next push .
	Slider* m_experienceSlider = nullptr; //Slider displaying the current experience.
	Button* m_pauseButton = nullptr; // Button that pauses the game.
	Button* m_muteButton = nullptr; //Button that mute the music.
	Button* m_nextLineButton = nullptr; //Button to spawn a new line of blocks.
	Button* m_playButton = nullptr; // Main menu play button.
	Button* m_replayButton = nullptr; //Replay button that appears when it is gameover
	Button* m_resumeButton = nullptr;
	Text* m_textBox = nullptr; //Central text box that displays level up, game over and pause messages.
	Text* m_scoreBox = nullptr; //Text box displaying the current score.
	Text* m_levelText = nullptr; //Text box displaying the current level.

	GameObject* m_limit = nullptr; //Texture limiting the region where the boxes can get to.
	GameObject* m_uiTopBox = nullptr; //Top UI box.
	GameObject* m_uiBottomBox = nullptr;//Bottom UI box.
	GameObject* m_menu = nullptr; //Menu object containing the logo texture.
	GameObject* m_blackScreen = nullptr; //Transition black screen.
	GameObject* m_floor = nullptr; //Grass floor object.
	GameObject* m_tutorial1 = nullptr; //Tutorial 1 screen object
	GameObject* m_tutorial2 = nullptr; //Tutorial 2 screen object
	std::array<PlaneAnimation*, 3> planes; //Planes animations going on the background.
	std::array<GameObject*, 4> clouds; //Cloud textures.

	const char* m_levelupText = "LEVEL UP!"; //Level up text message.
	const char* m_gameOverText = "GAME OVER"; //Game over text message.
	const char* m_pauseGameText = "GAME PAUSED"; //Game pause text message.
};

#endif // !GameManager_h



