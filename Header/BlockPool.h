#pragma once
#include <stack>
#include "Block.h"

#ifndef BlockPool_h
#define BlockPool_h


/// <summary>
/// Keeps a stack of blocks so the blocks are recyclable.
/// </summary>
class BlockPool
{
public:
	BlockPool(int maxBlocks); //Creates the pool of blocks with the number specified
	~BlockPool();
	Block* SpawnBlock(); //Returns a block from the pool. If there is not a block available, instantiates new one. 
	void ReturnBlock(Block* block);//Returns a block to the pool and resets it state.
	

private:
	std::stack<Block*> m_blockPool; //Contains all the blocks currently inactive.
	int m_maxBlocks; //Max number of blocks that the pool should have. Size of the board.
	int m_currentSize; //Current size of the pool of blocks.

};


#endif