//OpenGL_3_3Engine.cpp
//last update 03/16/2013

#include "OpenGL_3_3Engine.h"
#include "glInfo.h"
#include "Shader.h"

#include <cstdlib>
#include <ctime>
#include <sstream>
#include "MainApp.h"

namespace OpenGL_3_3Engine
{
	Engine::Engine()
	{
		srand(time(0));
		m_frameRate = 0;
		m_milliPerFrame = 0.0f;

		m_isPaused = false;

		m_appTitle = "OpenGL engine";


	}

	Engine::~Engine()
	{
	}

	bool Engine::Init(int width,int height,int depth,bool fullScreen)
	{

		m_screenWidth  = width;
		m_screenHeight = height;
		m_bitDepth     = depth;
		m_fullScreen   = fullScreen;

		

		if(glfwInit() != GL_TRUE)
		{
			std::cout <<"problem with glfw! can't init :(" <<  std::endl;
			return false;
		}

		//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
		//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		// Open a window and create its OpenGL context
		if( !glfwOpenWindow( width, height,8,8,8,8,32,32,GLFW_WINDOW ) )
		{
			fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
			glfwTerminate();
			return -1;
		}


		if(glewInit() != GLEW_OK)
		{
			std::cout <<"problem with glew! can't init :("<< (char*)glewGetErrorString(glewInit()) << std::endl;
			return false;
		}

		//Init DevIL library and states
		ilInit();
		ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
		ilEnable(IL_ORIGIN_SET);

		ilEnable(IL_TYPE_SET);
		ilTypeFunc(IL_UNSIGNED_BYTE);

		

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glDisable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		//glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glInfo::getInstance().Init();
		//glInfo::getInstance().PrintInfo();

		if(!GameInit())
			return false;

		return true;
	}

	void Engine::ShutDown()
	{
		gameOver = true;
	}

	void Engine::Update(double dt)
	{
		
		GameUpdate(dt);
		//std::cout<<m_frameRate<<std::endl;
		//std::cout<<m_milliPerFrame<<std::endl;
	}

	void Engine::StartRender()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	void Engine::EndRender()
	{
		glfwSwapBuffers();
	}

	void Engine::Render()
	{
		GameRender();
	}

	void Engine::Close()
	{
		glfwTerminate();
		GameEnd();
		
	}
};