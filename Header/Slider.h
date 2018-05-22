#pragma once
#include "GameObject.h"

#ifndef Slider_h
#define Slider_h


class Slider : public GameObject
{
public:
	Slider();
	~Slider();
	void SetFillTexture(const char* path);//Sets the fill texture of the slider.
	void Render() override; //Renders both of the textures of the slider.
	void SetMaxValue(float maxValue);//Sets the max value that the slider can take.
	void SetCurrentValue(float value);//Sets the current values of the slider. Should be between zero and Max Value.

private:
	float m_maxValue = 1; //Value that represents the maximum amount that the slider can represent.
	float m_value;//Current value of the slider.
	float m_sliderScale; //Represents the translation of the value into the width of the slider. Width is multiplied by this scale. 
	SDL_Texture* m_fill = nullptr; //Pointer to the fill texture, the texture that will increase and decrease size based on the values of the slider.
	SDL_Rect m_fillSrcRect, m_fillDestRect;//SDL rectangle of the fill texture.
};


#endif