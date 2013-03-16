//Timer.C
#include "Timer.h"
#include "OpenGL_3_3Engine.h"


Timer::Timer() {
	Start();
}

void Timer::Start() {
	m_startTime = glfwGetTime();
	m_currentTime = 0;
	m_elapsedTime = 0;
	m_FPS = 0;
}


void Timer::Idle() {

	static GLint tempFPS = 0;							
   	


	float newCurrentTime;
	
	newCurrentTime = glfwGetTime();		
	m_elapsedTime  = newCurrentTime - m_currentTime;
	m_currentTime = newCurrentTime;
	static float previousFPSTime = 0;

	
    while( newCurrentTime - previousFPSTime  > 0.033 ) {
		GameUpdate(0.033);
        previousFPSTime += 0.033;
    }

	m_currentTime = newCurrentTime;	
}

Timer* Timer::GetInstance(){
	if (!m_instance){
	  m_instance = new Timer();
	}

	return m_instance;
}

Timer* Timer::m_instance = NULL;