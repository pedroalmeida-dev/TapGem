#include "GameObject.h"
#include "ResourceManager.h"

GameObject::GameObject()
{	
	
}

GameObject::~GameObject()
{
	m_texture = nullptr;
}

void GameObject::Update(float deltaTime)
{
	
}

void GameObject::Render()
{
	//If the object is not visible -> do not draw it.
	if(!m_isVisible)
		return;
	
	SDL_RenderCopy(Game::renderer, m_texture, &m_srcRect, &m_destRect);
}

void GameObject::LoadTexture(const char * textureSheet)
{
	m_texture = ResourceManager::LoadTexture(textureSheet);
	//Updates the source rectangle
	SDL_QueryTexture(m_texture, NULL, NULL, &m_srcRect.w, &m_srcRect.h);
	//Updates the destination rectangle values 
	m_destRect.w = (int) (m_srcRect.w * m_scale.X);
	m_destRect.h = (int) (m_srcRect.h * m_scale.Y);

}

SDL_Texture * GameObject::GetTexture()
{
	return m_texture;
}

void GameObject::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
	//Updates the source rectangle
	SDL_QueryTexture(m_texture, NULL, NULL, &m_srcRect.w, &m_srcRect.h);	
	//Updates the destination rectangle values 
	m_destRect.w = (int) (m_srcRect.w * m_scale.X);
	m_destRect.h = (int) (m_srcRect.h * m_scale.Y);
}

Vector2 GameObject::GetPosition()
{
	return m_position;
}

void GameObject::SetPosition(Vector2 vector)
{
	m_position = vector;
	//Updates the destination rectangle position 
	m_destRect.x = (int) m_position.X;
	m_destRect.y = (int) m_position.Y;
}

void GameObject::SetPosition(float x, float y)
{
	m_position.X = (float) x;
	m_position.Y = (float) y;
	//Updates the destination rectangle position 
	m_destRect.x = (int) m_position.X;
	m_destRect.y = (int) m_position.Y;
}

void GameObject::SetScale(Vector2 scale)
{
	m_scale = scale;
	//Updates the texture scale
	m_destRect.w = m_srcRect.w * m_scale.X;
	m_destRect.h = m_srcRect.h * m_scale.Y;
}

void GameObject::SetScale(float x, float y)
{
	m_scale = Vector2(x, y);
	//Updates the texture scale
	m_destRect.w = (int) (m_srcRect.w * m_scale.X);
	m_destRect.h = (int) (m_srcRect.h * m_scale.Y);
}

void GameObject::SetVisibility(bool isVisible)
{
	m_isVisible = isVisible;
}

bool GameObject::IsVisible()
{
	return m_isVisible;
}

int GameObject::GetWidth()
{
	return m_destRect.w;
}

int GameObject::GetHeight()
{
	return m_destRect.h;
}


