//Texture.h - texture class
//last update 17/07/2012
#pragma once

#include "Includes.h"

namespace OpenGL_3_3Engine
{
	

	class Texture
	{
		public:
			Texture() {};
			~Texture(){glDeleteTextures(1,&m_handle);}

			bool Init(const char* filename,GLfloat magFilter,GLfloat minFilter,GLfloat sWrap,GLfloat tWrap);


			GLuint m_handle;
		
	};
};