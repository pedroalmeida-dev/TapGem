#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#ifndef ResourceManager_h
#define ResourceManager_h

class ResourceManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName); //Loads a texture based on the path provided and returns it. 
	static Mix_Chunk* LoadSound(const char* fileName); //Loads a sound based on the path provided and return it.
	static Mix_Music* LoadMusic(const char* fileName); //Loads a music file based on the path provided and returns it.
	static TTF_Font * LoadFont(const char* fileName, int size); //Loads a font based on the path provided and returns it.

private:
	ResourceManager();
	~ResourceManager();

};

#endif // !ResourceManager_h

