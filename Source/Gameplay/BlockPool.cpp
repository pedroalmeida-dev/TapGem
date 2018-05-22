#include "BlockPool.h"

BlockPool::BlockPool(int maxBlocks) : m_maxBlocks(maxBlocks)
{
	//Create the number or blocks required and adds them to the stack
	for(int i = 0; i < maxBlocks; i++)
	{	
		Block* block = new Block();
		m_blockPool.push(block);
		m_currentSize++;
	}
}

BlockPool::~BlockPool()
{
	//Delete all the block in the stack
	while(!m_blockPool.empty())
	{	
		Block* block = m_blockPool.top();
		delete block;
		block = nullptr;
		m_blockPool.pop();
		m_currentSize--;
	}	
}

Block* BlockPool::SpawnBlock()
{
	Block* block;
	//If stack if empty create instance of new block
	if(m_blockPool.empty())
	{
		block = new Block();
	}
	else //Else get the last block from the stack
	{
		block = m_blockPool.top();
		m_blockPool.pop();
		m_currentSize--;
	}
	//Sets the block visible
	block->SetVisibility(true);
	return block;
}

void BlockPool::ReturnBlock(Block* block)
{
	//Pool does not accept null pointers
	if(block == nullptr)
		return;
	//If the there are more blocks than the size of the board
	if(m_currentSize >= m_maxBlocks)
	{
		//Delete the returned block
		delete block;
		block = nullptr;
	}
	else
	{
		//Else reset the block and return it to the pool
		block->Reset();
		m_blockPool.push(block);
		m_currentSize++;
	}


}
