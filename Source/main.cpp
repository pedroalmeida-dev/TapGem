#include "SDL.h"
#include "Game.h"
#include "GameTime.h"
#include "GameConfig.h"
#include <iostream>

int main(int argc, char *argv[]) {

	//Sets the limit frame rate
	const int FRAME_RATE = 60;
	//Value used to limit the frame rate
	const float FRAME_DELAY = 1.0f / FRAME_RATE;
	//Instanciates the game class and initializes SDL window
	Game *game = new Game("Tap Gem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameConfig::SCREEN_WIDTH, GameConfig::SCREEN_HEIGHT, false);
	//Intanciates the gameTime Object used to keep track of the time passed in the game
	GameTime* gameTime = new GameTime(); 

	//Game Loop
	while(game->Running())
	{
		//Updates game Time
		gameTime->Update();
		//Check for SDL events
		game->HandleEvents();

		//When true render and update next frame
		if(gameTime->DeltaTime() >= FRAME_DELAY) 
		{	
			//Updates all objects
			game->Update(gameTime->DeltaTime());
			//Renders all ojbects
			game->Render();		
			//Resets gameTime, must be in the end of the update
			gameTime->Reset();
		}
	}	

	//Clean up
	delete game;
	game = nullptr;
	delete gameTime;
	gameTime = nullptr;
	return 0;
}