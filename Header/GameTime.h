#pragma once
#include <SDL.h>

#ifndef GameTime_h
#define GameTime_h

class GameTime
{
public:
	GameTime();
	~GameTime();

	void Reset();//Resets time variables before the next frame.
	void Update();//Updates the time variables for the current frame.
	float DeltaTime();  //Getter for the delta time.

private:
	int m_startTicks; //Number of total milliseconds on the start of the frame. 
	int m_elapsedTicks; //Number of miliseconds that the current frame took to run.
	float m_deltaTime; //Time that the last frame took to run, in seconds.
	float m_totalElapsedTime; //The total time the game has been running.
};

#endif

