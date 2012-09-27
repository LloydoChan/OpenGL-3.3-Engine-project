//Joypad.cpp - implementation of the joypad class

#include "Joypad.h"

namespace OpenGL_3_3Engine
{
	bool  Joypad::IsConnected()
	{
		return glfwGetJoystickParam(JoypadVals[m_playerNum],GLFW_PRESENT);
	}

	void  Joypad::Update()
	{
		//there are 10 buttons available on an xbox pad
		glfwGetJoystickButtons(JoypadVals[m_playerNum],m_currentState.buttons,10);
		glfwGetJoystickPos(JoypadVals[m_playerNum],m_currentState.axesValues,5);

		for(int axis = 0; axis < 5; axis++)
		{
			if(m_currentState.axesValues[axis] < 0.15f && m_currentState.axesValues[axis] > -0.15f)
				m_currentState.axesValues[axis] = 0.0f;
		}
	}

	float Joypad::GetStickValue(int stickAndAxis)
	{
		return m_currentState.axesValues[stickAndAxis];
	}

	int   Joypad::GetStickButton(int button)
	{
		return m_currentState.buttons[button];
	}
};