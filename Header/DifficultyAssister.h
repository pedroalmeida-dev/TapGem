#pragma once

#ifndef DifficultyAssister_h
#define DifficultyAssister_h

/// <summary>
/// Controls the difficulty of the game. When the block manager spawns a block 
/// it will get the type of block from the assister's methods. The assister generates the random values 
/// that identify the blocks. 
/// </summary>
class DifficultyAssister
{
public:
	DifficultyAssister();
	~DifficultyAssister();
	void Reset(); //Resets the game variables. The difficulty of the game can be tweaked here.
	void UpdateCurrentGameValues(int currentLevel); //Gets called when there is a level up, updating member variables.
	int SelectBlockColorValue(); //Generates a random int that identifies the color of a new block.
	int SelectBlockTypeValue(); //Generates a random int that identifies the type of a new block.
	float GetPushTime(); //Returns the values for the time until the next push of blocks.
	int GetNextLevelUp(); //Returns the experience value for the next level up.
	int GetPowerBlockUnlockLevel(); //Returns the level at which power blocks unlock.

private:

	int m_currentLevel; //Current level reached.
	int m_numberOfColors; //Number of max active colors of in the game. 	
	int m_powerBlockChance; //Probability of a powerBlock to spawn. Each unit is equivalent to 0.01%.
	int m_startingPushTime; //Initial time until the first push of the blocks.
	int m_nextLevelUp; //Experience to next level up.
	int m_powerBlockUnlockLevel; //Level at which the power blocks unlock.

};


#endif