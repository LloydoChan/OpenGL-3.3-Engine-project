//Timer.h

#pragma once
#include "Includes.h"


class Timer{
	public:
		void Start();
		void Idle();

	    float GetCurrentTime()	const {return m_currentTime;}	
		float GetElapsedTime()	const {return m_elapsedTime;}	
		int   GetFPSCounter()	const {return m_FPS;}	

		static Timer* GetInstance();
		void   DestroyInstance(){if(m_instance)delete m_instance;}
	private:
		
		Timer();
		~Timer(){};

		float			m_startTime;		
		float			m_currentTime;	
		float			m_elapsedTime;
		int				m_FPS;

		static Timer* m_instance;
};