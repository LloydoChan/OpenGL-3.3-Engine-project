//Texture.cpp
//Last updated: 17/07/2012

#include "Texture.h"

namespace OpenGL_3_3Engine
{
	

	bool Texture::Init(const char* filename,GLfloat magFilter,GLfloat minFilter,GLfloat sWrap,GLfloat tWrap)
	{

		glGenTextures(1,&m_handle);
		glBindTexture(GL_TEXTURE_2D,m_handle);
		
		int result = glfwLoadTexture2D(filename,0);

		
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,sWrap);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,tWrap);


		glBindTexture(GL_TEXTURE_2D,0);

		return true;

	}

	
}