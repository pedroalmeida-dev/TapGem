#include "MouseInput.h"

MouseState MouseInput::m_oldState = MouseState();
MouseState MouseInput::m_newState = MouseState();
Vector2 MouseInput::m_position = Vector2();


MouseInput::MouseInput()
{
}


MouseInput::~MouseInput()
{
}

bool MouseInput::IsLeftButtonDown()
{	
	if(m_newState.LeftMouseButton  == ButtonState::Pressed)
		if(m_oldState.LeftMouseButton == ButtonState::Released)
		{
			return true;
		}
		else
		{
			return false;
		}
	else
		return false;
}

bool MouseInput::IsLeftButtonUp()
{
	if(m_newState.LeftMouseButton == ButtonState::Released)
		if(m_oldState.LeftMouseButton == ButtonState::Pressed)
		{
			return true;
		}
		else
		{
			return false;
		}
	else
		return false;
}

bool MouseInput::IsRightButtonDown()
{
	if(m_newState.RightMouseButton == ButtonState::Pressed)
		if(m_oldState.RightMouseButton == ButtonState::Released)
		{
			return true;
		}
		else
		{
			return false;
		}
	else
		return false;
}

bool MouseInput::IsRightButtonUp()
{
	if(m_newState.RightMouseButton == ButtonState::Released)
		if(m_oldState.RightMouseButton == ButtonState::Pressed)
		{
			return true;
		}
		else
		{
			return false;
		}
	else
		return false;
}

Vector2 MouseInput::GetMousePosition()
{
	return m_position;
}

void MouseInput::SetLeftButtonState(bool pressed)
{
	if(pressed)
	{
		m_newState.LeftMouseButton = ButtonState::Pressed;
	}
	else
	{
		m_newState.LeftMouseButton = ButtonState::Released;
	}	
}

void MouseInput::SetRightButtonState(bool pressed)
{
	if(pressed)
	{
		m_newState.RightMouseButton = ButtonState::Pressed;
	}
	else
	{
		m_newState.RightMouseButton = ButtonState::Released;
	}
}

void MouseInput::UpdateOldState()
{
	m_oldState = m_newState;
}
