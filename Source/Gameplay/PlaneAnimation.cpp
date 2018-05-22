#include "PlaneAnimation.h"
#include "ResourceManager.h"
#include "GameConfig.h"
#include <time.h>

PlaneAnimation::PlaneAnimation()
{	
	SetTexture(ResourceManager::LoadTexture("Content/plane.png"));
	srand(time(NULL));
	m_timer = 0;
	m_spawnTime = (float) (rand() % 10);
	SetScale(0.4,0.4);
	SpawnPlane();
}

PlaneAnimation::~PlaneAnimation()
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}

void PlaneAnimation::Update(float deltaTime)
{
	if(m_movePlane)
	{
		//Increments the x position of the plane
		SetPosition(m_position.X += 2, m_position.Y);
		//If the plane is off screen
		if(m_position.X > GameConfig::SCREEN_WIDTH)
		{
			//Despawn the plane
			m_movePlane = false;
			SetVisibility(false);
			//Start spawn timer 
			m_spawnTime = rand() % 10;
			m_timer = 0;
		}
	}
	else
	{
		//After the plane has stop moving wait a random amount of time
		m_timer += deltaTime;
		if(m_timer > m_spawnTime)
		{
			//Then spawn the plane again
			SpawnPlane();
		}
	}
}

void PlaneAnimation::SpawnPlane()
{
	//Sets a random Y position
	int randNum = rand() % 340 + 100;
	SetPosition(-100, randNum);
	SetVisibility(true);
	//Stes the plane moving
	m_movePlane = true;
}
