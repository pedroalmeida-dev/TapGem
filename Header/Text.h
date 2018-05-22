#pragma once
#include "GameObject.h"
#include <SDL_ttf.h>

#ifndef Text_h
#define Text_h


class Text : public GameObject
{
public:
	Text();
	~Text();
	void Render() override;
	void LoadFont(const char* fileName, int size);	//Loads the font specified in the path provided, with the size provided.
	void UpdateTextBox(const char* text); // Updates the text box.Creates a new texture and replaces the old one with the new text.
	void UpdateTextBox(const char* text, SDL_Color textColor);//Updates the text box. Creates a new texture and replaces the old one with the new text and color.
	void SetColor(SDL_Color textColor);//Setter for the color of the texture. The texture must be updates after this is called.
	void SetCenterOrigin(bool isCenter);//Used to set the center of the texture has the origin.
private:
	SDL_Color m_textColor = { 0, 0, 0 }; //Text default color.
	TTF_Font* m_font = nullptr; //Font used to draw the text texture.
	bool m_isOriginCenter; //If true the origin postion of the texture will be its center.

};


#endif