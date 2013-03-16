//testMain.cpp
#include <iostream>
#include "..\OpenGL_3_3Engine\OpenGL_3_3Engine.h"
#include "TestEngine\TestApp.h"


TestApp* app;

bool GamePreload()
{
	//g_engine->Init(640,480,3,false);
	app = new TestApp();
	return true;
}

bool GameInit()
{
	app->Init();
	return true;
}

void GameUpdate(double dt)
{
	app->Update(dt);
}

void GameRender()
{
	app->Render();	
}

void GameEnd()
{
	app->Shutdown();
}