#include "DifficultyAssister.h"
#include <time.h>
#include <stdlib.h> 

DifficultyAssister::DifficultyAssister()
{
	srand(time(NULL));	
	Reset();
}

DifficultyAssister::~DifficultyAssister()
{

}

void DifficultyAssister::Reset()
{
	//Change the difficulty of the game by changing these values
	m_numberOfColors = 4;
	m_currentLevel = 1;
	m_powerBlockChance = 2;
	m_startingPushTime = 10;
	m_nextLevelUp = 250;
	m_powerBlockUnlockLevel = 4;
}

void DifficultyAssister::UpdateCurrentGameValues(int currentLevel)
{
	m_currentLevel = currentLevel;
	//Increases the probability of power blocks by 0.1 every level up
	if(m_currentLevel > m_powerBlockUnlockLevel)
		m_powerBlockChance++;

	//Increases the number of colors in the game by leveling up
	if(m_currentLevel <= 5)
	{
		m_numberOfColors = 4;
	}
	else if(m_currentLevel <= 12)
	{
		m_numberOfColors = 5;
	}
	else
	{
		m_numberOfColors = 6;		
	}
}

int DifficultyAssister::SelectBlockColorValue()
{
	int randNum = rand() % m_numberOfColors;
	return randNum;
}

int DifficultyAssister::SelectBlockTypeValue()
{
	//Special blocks are only unlocked after level 4
	if(m_currentLevel <= m_powerBlockUnlockLevel)
		return 0;

	int randNum = rand() % 1000;
	if(randNum <= 1000 - m_powerBlockChance * 4)
	{
		randNum = 0; //Identifies normal block
	}
	else if (randNum <= 1000 - m_powerBlockChance * 3)
	{
		randNum = 1; //Identifies the bomb
	}
	else if(randNum <= 1000 - m_powerBlockChance * 2)
	{
		randNum = 2; //Identifies the lightning
	}
	else if(randNum <= 1000 - m_powerBlockChance)
	{
		randNum = 3; //Identifies the sword
	}
	else
	{
		randNum = 0;
	}
	return randNum;
}

float DifficultyAssister::GetPushTime()
{
	int pushTime;
	//The next push will be 0.25 seconds faster than the previous level
	pushTime = m_startingPushTime - 0.25 * m_currentLevel; 

	//The push time cannot be lower than 3
	if(pushTime < 3)
		return 3;
	else
		return pushTime;

}

int DifficultyAssister::GetNextLevelUp()
{
	//Each level up the required experience points increase by 20 percent
	return m_nextLevelUp += m_nextLevelUp * 0.15;
}

int DifficultyAssister::GetPowerBlockUnlockLevel()
{
	return m_powerBlockUnlockLevel;
}
