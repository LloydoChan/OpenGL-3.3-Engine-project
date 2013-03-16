//MainApp.cpp
//Last updated: 14/07/2012
#include "MainApp.h"
#include "OpenGL_3_3Engine.h"

bool gameOver;

OpenGL_3_3Engine::Engine *g_engine;

int main()
{
	g_engine = new OpenGL_3_3Engine::Engine();

	if(!GamePreload())
	{
		std::cerr <<"Problem with the game preload info"<<std::endl;
		return 0;
	}

	if(!g_engine->Init(640,480,32,false))
	{
		std::cerr<<"Problem initialising the engine"<<std::endl;
		return 0;
	}



	gameOver = false;

	while(!gameOver)
	{
		Timer::GetInstance()->Idle();
		g_engine->StartRender();
		g_engine->Render();
		g_engine->EndRender();
	}

	g_engine->Close();
	delete g_engine;

	return 1;
}