#include "ResourceManager.h"
#include "Game.h"
#include <cstdio>


ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{

}

SDL_Texture * ResourceManager::LoadTexture(const char * fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	if(tmpSurface == nullptr)
	{
		printf("Unable to load texture file: %s - %s\n", fileName, IMG_GetError());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	if(texture == nullptr)
	{
		printf("Unable to create texture from surface: %s\n", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(tmpSurface);
	return texture;
}

Mix_Chunk * ResourceManager::LoadSound(const char * fileName)
{
	Mix_Chunk* soundEffect = Mix_LoadWAV(fileName);
	if(soundEffect == nullptr)
	{
		printf("Unable to load sound file: %s\n", Mix_GetError());
		return nullptr;
	}
	return soundEffect;
}

Mix_Music * ResourceManager::LoadMusic(const char * fileName)
{
	Mix_Music* music = Mix_LoadMUS(fileName);
	if(music == nullptr)
	{
		printf("Unable to load music file: %s\n", Mix_GetError());
		return nullptr;
	}
	return music;
}

TTF_Font* ResourceManager::LoadFont(const char* fileName, int size)
{
	TTF_Font* font = TTF_OpenFont(fileName, size);
	if(font == nullptr)
	{
		printf("Unable to load font file: %s\n", TTF_GetError());
		return nullptr;
	}
	return font;
}

