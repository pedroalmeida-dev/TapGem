#pragma once
#include "GameObject.h"
#include <random>
#include <functional>

#ifndef Block_h
#define Block_h


// Represents all the possible colors of the blocks.
enum class BlockColor 
{
	None,
	Blue,
	Red,
	Yellow,
	Green,
	Purple,
	Grey,
};

//Represents all the possible block types.
enum class BlockType
{
	Normal,
	Bomb,
	Sword,
	Lightning,
};


/// <summary>
/// Represents an indivudual block in the game.
/// </summary>
class Block : public GameObject
{
public:
	Block();
	~Block();
	void Reset(); //Resets the block variables to its initial state
	void Update(float deltaTime) override;	//Updates the block animation when it is active.
	void Render() override; //Sets the color of the texture depending on the color of the block
	void SetPosition(Vector2 vector) override; //If the block is falling and gets assigned a new position cancel the animation
	void SetPosition(float x, float y) override;//If the block is falling and gets assigned a new position cancel the animation
	BlockColor GetColor(); //Getter for the color of the block.
	void SetColor(BlockColor color); // Setter for the color of the block
	BlockType GetType(); // Getter for the type of the block.
	void SetType(BlockType type); // Setter for the ty of block
	void SetClicked(bool clicked); // Setter that states that the block was clicked
	bool WasClicked(); // Getter to check if the block was clicked
	void SetTapped(bool isTapped); // Setter that states if the block was tapped.
	bool IsTapped(); //Getter to check if the block iwas already tapped.
	void ApplyForce(float x, float y); //Activates the animation and gives a initial force upwards, the x component sets the direction.
	bool IsOffScreen(); // Checks if the block as left the screen
	void TriggerFallDown(Vector2 pos);//Triggers the block to fall down to the position passed in the parameters
	

private:

	SDL_Color GetColorValue(BlockColor color); //Retreives the rbg values for a specific BlockColor.
	void Animate(float deltaTime); //Uses phisics to animate the block, making it fall.	
	void CheckStopFalling();//Checks if the block should stop falling.

	BlockColor m_color = BlockColor::None; //Color of the block. Bombs and swords have not color.
	BlockType m_type = BlockType::Normal;  //Type of the block. See enum BlockType.
	bool m_wasClicked; //Prevents the block to be clicked twice
	bool m_isTapped; //Prevents the block to be tapped twice	

	/* Animation */
	Vector2 m_velocity; //Velocity of the block;
	Vector2 m_acceleration; //Accelaration of the block
	float m_damping; //Damp coeficient 
	float m_inverseMass; //Inverse of the mass 
	bool m_isAnimated; //States if the block is currently in animated state, gravity is on.
	Vector2 m_positionToFallTo; //While the block is falling, this is the position that he will fall to
	bool m_isFalling; //States if the block is currently falling down, to replace a block that was tapped bellow

	static int numOfBlocks; //Total number of block instances. Used for debug.
};


#endif