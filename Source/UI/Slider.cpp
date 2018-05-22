#include "Slider.h"
#include "Vector2.h"
#include "SDL.h"
#include "ResourceManager.h"


Slider::Slider()
{
	m_isVisible = true;
	m_value = 0.5;
}


Slider::~Slider()
{
	SDL_DestroyTexture(m_fill);
	m_fill = nullptr;
}

void Slider::SetFillTexture(const char* path)
{
	m_fill = ResourceManager::LoadTexture(path);
	//Updates rectangles
	SDL_QueryTexture(m_fill, NULL, NULL, &m_fillSrcRect.w, &m_fillSrcRect.h);	
	m_fillDestRect.w = (int) ((m_fillSrcRect.w * m_scale.X) * m_sliderScale);
	m_fillDestRect.h = (int) (m_fillSrcRect.h * m_scale.Y);
	m_fillDestRect.x = (int) m_position.X;
	m_fillDestRect.y = (int) m_position.Y;
}

void Slider::Render()
{
	//Renders background texture of the slider
	GameObject::Render();	
	//Renders the fill texture of the slider based on the current and max value 
	SDL_RenderCopy(Game::renderer, m_fill, &m_fillSrcRect, &m_fillDestRect);
}

void Slider::SetMaxValue(float maxValue)
{
	m_maxValue = maxValue;
	//Updates the scale of the slider fill when the max value changes
	m_sliderScale = m_value / m_maxValue;
	m_fillDestRect.w = (int)((m_fillSrcRect.w * m_scale.X) * m_sliderScale);
}

void Slider::SetCurrentValue(float value)
{
	m_value = value;
	//Updates the scale of the slider fill when the value changes
	m_sliderScale = m_value / m_maxValue;
	m_fillDestRect.w = (int)((m_fillSrcRect.w * m_scale.X) * m_sliderScale);
}



