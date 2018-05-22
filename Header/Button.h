#pragma once
#include "GameObject.h"

#ifndef Button_h
#define Button_h


class Button : public GameObject
{
public:
	Button();
	~Button();
	void Update(float deltaTime) override;	//Calls the IsHoveringMethod();
	void Render() override; //Render the button active texture
	void LoadTexture(const char * textureSheet)override; //Hover and Pressed textures are also set if they have not been loaded.
	bool GotPressed(); //Checks if the button has been pressed in the current frame
	void ToogleButton(); //If the button is not pressed, press it, changing the texture, and vice-versa.
	void LoadHoverTexture(const char* textureName); //Loads the hover texture
	void LoadPressedTexture(const char* textureName); //Loads the Pressed texture

private:
	bool IsHovering(); //Checks if the mouse is hovering over the button

	bool m_isPressed; //States if the button is currently pressed
	Vector2 m_mousePos; //Mouse Position
	SDL_Texture* m_activeTex = nullptr; // The current active texture of the button
	SDL_Texture* m_hoveringTex = nullptr; // The texture of the button when the mouse is hovering
	SDL_Texture* m_pressedTex = nullptr; // The texture of the button when it is pressed
};


#endif