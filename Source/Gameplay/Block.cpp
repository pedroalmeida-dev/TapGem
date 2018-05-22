#include "Block.h"
#include "GameConfig.h"
#include <time.h>

int Block::numOfBlocks = 0;

Block::Block()
{
	Reset();
	numOfBlocks++;
	//std::cout << numOfBlocks << std::endl;
}


Block::~Block()
{
	m_texture = nullptr;
	numOfBlocks--;
	//std::cout << numOfBlocks << std::endl;
}

void Block::Reset()
{
	m_isVisible = false;
	m_wasClicked = false;
	m_isTapped = false;
	m_velocity = Vector2();
	m_acceleration = Vector2();
	m_damping = 0.9;
	m_inverseMass = 0.5;
	m_isAnimated = false;
	m_isFalling = false;
	m_positionToFallTo = Vector2(0, 1000);
}

void Block::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	if(m_isAnimated)
	{
		//Apply phisics to the block
		Animate(deltaTime);
		//If the block is not tapped but is falling -> check for when it is time to fall
		if(!m_isTapped && m_isFalling)
			CheckStopFalling();
	}
	
}

void Block::Render()
{
	//If the block is not visible -> do not draw it.
	if(!m_isVisible)
		return;
	
	//If block type is not normal
	if(GetType() != BlockType::Normal)
	{
		//Set the color for the texture of the block
		SDL_Color color = GetColorValue(m_color);
		SDL_SetTextureColorMod(m_texture, color.r, color.g, color.b);
	}
	SDL_RenderCopy(Game::renderer, m_texture, &m_srcRect, &m_destRect);

}

void Block::SetPosition(Vector2 vector)
{
	//If a block gets a new position before finishing the animation
	if(m_isFalling)
	{
		//Cancels the animations
		m_isFalling = false;
		m_isAnimated = false;
		m_positionToFallTo.Y = 1000;
		
	}
	GameObject::SetPosition(vector);
	
}

void Block::SetPosition(float x, float y)
{
	//If a block gets a new position before finishing the animation
	if(m_isFalling)
	{
		//Cancels the animations
		m_isFalling = false;
		m_isAnimated = false;
		m_positionToFallTo.Y = 1000;	
	}
	GameObject::SetPosition(x, y);

	
}

BlockColor Block::GetColor()
{
	return m_color;
}

void Block::SetColor(BlockColor color)
{
	m_color = color;
}

BlockType Block::GetType()
{
	return m_type;
}

void Block::SetType(BlockType type)
{
	m_type = type;
}

void Block::SetClicked(bool clicked)
{
	m_wasClicked = clicked;
}

bool Block::WasClicked()
{
	return m_wasClicked;
}

void Block::SetTapped(bool isTapped)
{
	m_isTapped = isTapped;
}

bool Block::IsTapped()
{
	return m_isTapped;
}

void Block::ApplyForce(float x, float y)
{
	m_isAnimated = true;
	m_isFalling = false;
	//Creates the push force vector
	Vector2 force = Vector2(x, y) * 15;
	//Applies the force to the block
	m_acceleration += (force * m_inverseMass);
}

bool Block::IsOffScreen()
{
	if(m_position.X >= GameConfig::SCREEN_WIDTH || m_position.Y >= GameConfig::SCREEN_HEIGHT || m_position.X <= 0 || m_position.Y <= 0)
		return true;

	return false;
}

void Block::TriggerFallDown(Vector2 pos)
{		
	//Sets the position to fall to
	m_positionToFallTo.X = pos.X;
	m_positionToFallTo.Y = pos.Y;
	//triggers the animation
	m_isAnimated = true;
	m_isFalling = true;	
}

SDL_Color Block::GetColorValue(BlockColor color)
{
	switch(color)
	{
		case BlockColor::Blue:
			return{ 74, 191, 240 };
			break;
		case BlockColor::Red:
			return{ 242, 55, 55 };
			break;
		case BlockColor::Green:
			return{ 159, 206, 49 };
			break;
		case BlockColor::Purple:
			return{ 131, 89, 149 };
			break;
		case BlockColor::Yellow:
			return{ 255, 204, 0 };
			break;
		case BlockColor::Grey:
		default:
			return{ 255, 255, 255 };
			break;
	}
}

void Block::Animate(float deltaTime)
{	
	//Set gravitational force
	m_acceleration += (Vector2(0, 9.8) * m_inverseMass);
	//Applies damping
	m_velocity *= m_damping;
	//Applies accelaration and keeps the animation going at the same speed independent of frame rate
	m_velocity += m_acceleration * deltaTime * 8;
	//Applies the velocity to the entity position
	GameObject::SetPosition(m_position += m_velocity);
	//Reset accelaration for the next frame
	m_acceleration = Vector2();

}

void Block::CheckStopFalling()
{	
	//While the block if falling, if the y position goes over the position that it should be
	if(m_position.Y >= m_positionToFallTo.Y)
	{
		//Stops the animation
		m_isFalling = false;
		m_isAnimated = false;
		//Sets the correct position
		GameObject::SetPosition(m_positionToFallTo);
		//the the target Y position so it does not interrupt the destroy anymation
		m_positionToFallTo.Y = 1000;
	}
}
