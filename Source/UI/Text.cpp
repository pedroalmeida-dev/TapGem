#include "Text.h"
#include "ResourceManager.h"

Text::Text()
{
	m_isOriginCenter = false;
}

Text::~Text()
{
    TTF_CloseFont(m_font);
	m_font = nullptr;
}

void Text::Render()
{
	if(!m_isVisible)
		return;
		
	
	SDL_RenderCopy(Game::renderer, m_texture, &m_srcRect, &m_destRect);
}

void Text::LoadFont(const char * fileName, int size)
{
	m_font = ResourceManager::LoadFont(fileName, size);

}

void Text::UpdateTextBox(const char * text)
{
	//Cleans up the hold texture first
	SDL_DestroyTexture(m_texture);

	//Cannot continue if a font has not been loaded
	if(m_font == nullptr)
	{
		printf("Unable to create text texture: No font loaded\n");
		return;
	}
	//Creates a surface based on the font, the text and the color
	SDL_Surface * tmpSurface = TTF_RenderText_Solid(m_font, text, m_textColor);
	if(tmpSurface == nullptr)
	{
		printf("Unable to create text surface: %s : %s\n", text,  IMG_GetError());
		return;
	}
	//Creates a texture based on the surface 
	m_texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	if(m_texture == nullptr)
	{
		printf("Unable to create texture from surface: %s\n", SDL_GetError());
		return;
	}
	
	//Updates the rectangles used to render the texture
	SDL_QueryTexture(m_texture, NULL, NULL, &m_srcRect.w, &m_srcRect.h);
	m_destRect.w = (int)(m_srcRect.w * m_scale.X);
	m_destRect.h = (int)(m_srcRect.h * m_scale.Y);
	//Sets diferent positions depending on the origin
	if(m_isOriginCenter)
	{
		m_destRect.x = (int)(m_position.X - m_destRect.w / 2);
		m_destRect.y = (int)(m_position.Y - m_destRect.h / 2);
	}
	else
	{
		m_destRect.x = (int) m_position.X;
		m_destRect.y = (int) m_position.Y;
	}

	//Destroy the temporary surface
	SDL_FreeSurface(tmpSurface);

}

void Text::UpdateTextBox(const char * text, SDL_Color textColor)
{
	//Change the color of the texture 
	m_textColor = textColor;
	UpdateTextBox(text);
}

void Text::SetColor(SDL_Color textColor)
{
	m_textColor = textColor;
}

void Text::SetCenterOrigin(bool isCenter)
{
	m_isOriginCenter = isCenter;
}





