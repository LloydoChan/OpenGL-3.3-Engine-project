//TestApp.h - simple class based app to test the engine
#pragma once
#include "..\..\OpenGL_3_3Engine\OpenGL_3_3Engine.h"
#include "Cube.h"
#include "FullscreenQuad.h"



using namespace OpenGL_3_3Engine;


class TestApp
{
	public:
		TestApp();
		~TestApp(){};

		bool Init();
		void Render();
		void Shutdown();

		void Update(double dt){};
		void ReadInput();
		
	private:
		ObjectData*		             m_objBuffer;
		ResourceManager<Shader>*  	 m_shaderMan;
		ResourceManager<Texture>*    m_texMan;
		ResourceManager<StaticMesh>* m_meshMan;
		GLuint m_shaderHandle;
		GLuint m_meshHandle;
};