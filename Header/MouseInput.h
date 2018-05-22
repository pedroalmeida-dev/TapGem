#pragma once
#include <iostream>
#include "Vector2.h"

#ifndef MouseIntup_h
#define MouseInput_h

/// <summary>
/// Represents a button state in any given time. Buttons can have one of two states.
/// </summary>
enum ButtonState
{
	Released,
	Pressed
};

/// <summary>
/// Agregates the button states for both left and right mouse buttons.
/// </summary>
struct MouseState
{
	ButtonState LeftMouseButton;
	ButtonState RightMouseButton;
};

/// <summary>
/// Static class that keeps a state of mouse. Can be called to check on mouse button events and mouse position.
/// The Game class receives the SDL events and updates the mouse states. 
/// </summary>
class MouseInput
{
public:
	friend class Game; //The Game class cis the only one that can update the mouse state.
	static bool IsLeftButtonDown();//Returns true if the left mouse button has pressed on the current frame.  
	static bool IsLeftButtonUp();//Returns true if the left mouse button stopped being pressed in the current frame.
	static bool IsRightButtonDown();//Returns true if the right mouse button has pressed on the current frame. 
	static bool IsRightButtonUp();//Returns true if the right mouse button stopped being pressed in the current frame.
	static Vector2 GetMousePosition();//Returns the current mouse position. 

private:
	MouseInput();
	~MouseInput();

	static void UpdateOldState(); //Sets oldstate to the values of this frame mouse state.
	static void SetLeftButtonState(bool pressed);//Updates the left mouse button state.
	static void SetRightButtonState(bool pressed);//Updates the right mouse button state.
	static MouseState m_oldState;//State of the mouse in the last frame.
	static MouseState m_newState; //State of the mouse in the current frame.
	static Vector2 m_position;//Current position of the mouse.

};



#endif // !MouseIntup_h



