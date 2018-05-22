#include "Button.h"
#include "MouseInput.h"
#include "ResourceManager.h"


Button::Button()
{
	m_isVisible = true;
	m_activeTex = m_texture;
	m_isPressed = false;
	m_mousePos = Vector2();
}


Button::~Button()
{	
	SDL_DestroyTexture(m_hoveringTex);
	SDL_DestroyTexture(m_pressedTex);
	m_hoveringTex = nullptr;
	m_pressedTex = nullptr;
}

void Button::Update(float deltaTime)
{
	IsHovering();
}

void Button::Render()
{
	if(!m_isVisible)
		return;

	SDL_RenderCopy(Game::renderer, m_activeTex, &m_srcRect, &m_destRect);
}

void Button::LoadTexture(const char * textureSheet)
{
	GameObject::LoadTexture(textureSheet);	
	m_activeTex = m_texture;
	//If hover tex is null, set it the same to m_texture
	if(m_hoveringTex == nullptr)
		m_hoveringTex = m_texture;
	//If pressed tex is null, set it the same to m_texture
	if(m_pressedTex == nullptr)
		m_pressedTex = m_texture;
}

bool Button::GotPressed()
{
	//If the mouse is hovering and clicked the button 
	if(IsHovering() && MouseInput::IsLeftButtonDown())
	{		
		//Toogle the state of the button
		ToogleButton();
		return true;
	}
	else
	{
		return false;
	}
	
}

void Button::ToogleButton()
{
	if(m_isPressed)
	{
		m_activeTex = m_texture;
		m_isPressed = false;
	}
	else
	{
		if(m_pressedTex)
		m_activeTex = m_pressedTex;
		m_isPressed = true;
	}
}

void Button::LoadHoverTexture(const char * textureName)
{
	m_hoveringTex = ResourceManager::LoadTexture(textureName);
}

void Button::LoadPressedTexture(const char * textureName)
{
	m_pressedTex = ResourceManager::LoadTexture(textureName);
}

bool Button::IsHovering()
{
	//Gets the current mouse position
	m_mousePos = MouseInput::GetMousePosition();
	//Check for collsion with the button 
	if(m_mousePos.X > m_destRect.x && m_mousePos.X <  m_destRect.x + m_destRect.w && m_mousePos.Y > m_destRect.y && m_mousePos.Y < m_destRect.y + m_destRect.h)
	{
		//If the button is not pressed -> set the hovering texture
		if(!m_isPressed)
			m_activeTex = m_hoveringTex;
		return true;
	}
	else
	{
		//If the mouse if not hovering the button -> set the correct active texture
		if(m_activeTex == m_hoveringTex)
		{
			if(m_isPressed)
				m_activeTex = m_pressedTex;
			else
				m_activeTex = m_texture;
		}
		return false;
	}
}

