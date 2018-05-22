#include "GameTime.h"



GameTime::GameTime()
{
	Reset();
	m_totalElapsedTime = 0;
}


GameTime::~GameTime()
{
}

void GameTime::Reset()
{
	m_startTicks = SDL_GetTicks();
	m_elapsedTicks = 0;
	m_deltaTime = 0.0f;
}

void GameTime::Update()
{	
	m_elapsedTicks = SDL_GetTicks() - m_startTicks;
	m_deltaTime = m_elapsedTicks * 0.001f;
}

float GameTime::DeltaTime()
{
	return m_deltaTime;
}
