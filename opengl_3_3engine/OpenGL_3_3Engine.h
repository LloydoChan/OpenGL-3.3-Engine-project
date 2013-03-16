//OpenGL_3_3Engine.h
//last update: 01/08/2012

#pragma once

#include "Includes.h"
#include "Shader.h"
#include "ObjectData.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Texture.h"
#include "CubeMap.h"
#include "Framebuffer.h"
#include "Script.h"
#include "Audio.h"
#include "Joypad.h"
#include "StaticMesh.h"
#include "CubeRigidBody.h"
#include "SphereRigidBody.h"
#include "Timer.h"
#include "Quad.h"
#include "Frustum.h"
#include "SkyDome.h"
extern bool gameOver;
extern bool GamePreload();
extern bool GameInit();
extern void GameRender();
extern void GameUpdate(double dt);
extern void GameEnd();


namespace OpenGL_3_3Engine
{
	class Engine
	{
		public:
		
			Engine();
			virtual ~Engine();

			bool Init(int width,int height,int depth,bool fullscreen);
			void Close();

			void Update(double dt);

			void ShutDown();


			void StartRender();
			void EndRender();
			void Render();

			bool m_fullScreen;
			int  m_screenHeight;
			int  m_screenWidth;
			int  m_bitDepth;
			bool m_isPaused;

			long m_frameRate;

			double m_milliPerFrame;

			std::string m_appTitle;

	};
};

extern OpenGL_3_3Engine::Engine* g_engine;

//end of file