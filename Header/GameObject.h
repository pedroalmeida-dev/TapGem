#pragma once
#include "Game.h"
#include "Vector2.h"

#ifndef  GameObject_h
#define GameObject_h

/// <summary>
/// Base class for all game objects that are placed in the world.
/// </summary>
class GameObject
{

public:
	GameObject();
	~GameObject();

	virtual void Update(float deltaTime);//Updates the object logic. 
	virtual void Render(); //Renders the object. 

	virtual void LoadTexture(const char* textureSheet);//Load a texture using the resource manager, based on the path provided has parameters.
	SDL_Texture* GetTexture();//Getter for the Texture.
	void SetTexture(SDL_Texture* texture);//Setter for the texture. 
	Vector2 GetPosition();//Getter for the position.
	virtual void SetPosition(Vector2 vector);//Setter for the position.
	virtual void SetPosition(float x, float y);//Setter for the position. 
	void SetScale(Vector2 scale);//Setter for the scale.
	void SetScale(float x, float y);//Setter for the scale.
	void SetVisibility(bool isVisible);//Set the visibility of the texture, depending on the parameter passed.
	bool IsVisible();//Checks if the object is visible or not.
	int GetWidth();//Returns the width of the texture.
	int GetHeight();//Returns the height of the texture.

protected:
	bool m_isVisible = true; //If true the texture is rendered
	Vector2 m_position = Vector2(); //Current position of the gameobject. Should not be change directly or else does not effect the texture.
	Vector2 m_scale = Vector2(1, 1);//Current scale of the object, changes the size of the texture. Should not be change directly or else does not effect the texture.
	SDL_Texture* m_texture = nullptr; //Pointer to the texture of this gameobject. Does not delete texture by default. 
	SDL_Rect m_srcRect, m_destRect; //SDL rectangles used to render the texture.
};


#endif // ! GameObject_h



