//Joypad.h - a class that enables the use of an xbox control pad using glfw's lovely
//and convenient functions.
//last update: 01/08/2012

#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	//glfw can support up to 16 (!!!!!) joysticks, however four is a sensible/realistic amount
	const int JoypadVals[] = {GLFW_JOYSTICK_1,GLFW_JOYSTICK_2,GLFW_JOYSTICK_3,GLFW_JOYSTICK_4};


	//some constant values to make accessing data easier, e.g GetStickButton(A) instead of GetStickButton(0)

	const int A				= 0;
	const int B				= 1;
	const int X				= 2;
	const int Y				= 3;
	const int LB			= 4;
	const int RB			= 5;
	const int BACK			= 6;
	const int START			= 7;
	const int RIGHT_CLICK	= 8;
	const int LEFT_CLICK	= 9;


	//values of the sticks are stored in a 4 value float array, the below consts can help
	//access the data
	const int LEFT_STICK_X_AXIS    = 0;
	const int LEFT_STICK_Y_AXIS    = 1;
	const int RIGHT_STICK_X_AXIS   = 2;
	const int RIGHT_STICK_Y_AXIS   = 3;


	class Joypad
	{
		public:
			Joypad(int player)
			{   
				assert(player >= 0 && player < 4 && "You tried initialising a player lower than 0, higher than 3!!");
				m_playerNum=player;
			}

			~Joypad() {};

			bool  IsConnected();
			void  Update();
			float GetStickValue(int stickAndAxis);
			int   GetStickButton(int button);

		private:

			struct PadState
			{
				float axesValues[5];
				unsigned char buttons[10];
			};

			
			PadState m_currentState;
			int m_playerNum;

	};
};