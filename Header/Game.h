#pragma once
#include <SDL.h>



#ifndef Game_h
#define Game_h

/// <summary>
/// Game Kernel, games systems are created here to be updated and rendered.
/// </summary>
class Game
{
public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();
	void HandleEvents(); //Handles SDL events.
	void Update(float deltaTime);//Updates game systems every frame.
	void Render(); //Renders all objects. 
	bool Running(); //States if the game is running or not. 
	static SDL_Renderer *renderer; //Renderer 

private:
	bool m_isRunnning; // states if the game is running.
	SDL_Window *m_window = nullptr; //SDL game window.

};




#endif


