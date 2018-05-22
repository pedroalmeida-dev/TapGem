#include "Game.h"
#include "MouseInput.h"
#include "GameManager.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

GameManager* gameManager = nullptr;

SDL_Renderer* Game::renderer = nullptr;

Game::Game(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!..." << std::endl;
		m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if(m_window)
		{
			std::cout << "Window created." << std::endl;
		}

		renderer = SDL_CreateRenderer(m_window, -1, 0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 213, 237, 247, 255);
			std::cout << "Renderer created." << std::endl;
		}

		//Initialize SDL_mixer 
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

		}

		//Initialize SDL_TTF
		if(TTF_Init() < 0)
		{
			printf("SDL_TTF could not initialize! Error: %s\n", TTF_GetError());
		}

		m_isRunnning = true;
		//Initialize TapGem's Game systems
		gameManager = new GameManager();

	}
	else
	{
		m_isRunnning = false;
	}
}

Game::~Game()
{
	delete gameManager;
	gameManager = nullptr;

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(renderer);

	m_window = nullptr;
	renderer = nullptr;

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT: //Quit applcation
			m_isRunnning = false;
			break;

		case SDL_MOUSEBUTTONDOWN: //Check for mouse button down event
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				MouseInput::SetLeftButtonState(true);
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				MouseInput::SetRightButtonState(true);
			}
			break;

		case SDL_MOUSEBUTTONUP: //Check for mouse button up event
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				MouseInput::SetLeftButtonState(false);
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				
				MouseInput::SetRightButtonState(false);
			}
			break;

		case SDL_MOUSEMOTION: //Check for mouse motion events
		{
			int x = event.motion.x;
			int y = event.motion.y;			
			MouseInput::m_position = Vector2(x,y);
			break;
		}

		case SDL_WINDOWEVENT: //Check for window events
			switch(event.window.event)
			{
				case SDL_WINDOWEVENT_FOCUS_LOST:
					gameManager->LostFocus();
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					gameManager->GainedFocus();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Game::Update(float deltaTime)
{
	//Updates game systems
	gameManager->Update(deltaTime);
	//Sets the mouse last state to the one in this frame
	MouseInput::UpdateOldState();
}

void Game::Render()
{
	//Clear Renderer
	SDL_RenderClear(renderer);
	//Render all objects	
	gameManager->Render();	
	//Present the Renderer
	SDL_RenderPresent(renderer);

}

bool Game::Running()
{
	return m_isRunnning;
}
