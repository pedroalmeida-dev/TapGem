#pragma once
#include "GameObject.h"

#ifndef PlaneAnimation_h
#define PlaneAnimation_h

/// <summary>
/// Controls the difficulty of the game. When the block manager spawns a block 
/// it will get the type of block from the assister's methods. The assister returns values 
/// </summary>
class PlaneAnimation : public GameObject
{
public:
	PlaneAnimation();
	~PlaneAnimation();
	void Update(float deltaTime) override; //Updates the planes positions and resets them when they reach the end of the screen.

private:
	void SpawnPlane(); //Puts the plain the in left side of the screen with a random Y position.	
	float m_timer; //When a plain reach the end of the screen it doesn't immediately.
	float m_spawnTime; //Interval between plane spawns. Is randomized between each spawn.
	bool m_movePlane; //When true the plain is moving in the background.

};


#endif