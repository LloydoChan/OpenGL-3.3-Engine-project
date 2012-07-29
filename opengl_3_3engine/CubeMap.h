//CubeMap.h - 
//last update 17/07/2012

#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	class CubeMap
	{
	public:
		CubeMap(){};
		~CubeMap(){ glDeleteTextures(1,&m_handle);}

		bool Init(const char* filename);

		GLuint m_handle;
	};
}