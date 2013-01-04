//Framebuffer.h
#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	class Framebuffer
	{
		public:
			Framebuffer():m_FBOhandle(0),m_texHandle(0),m_depthHandle(0),m_height(0),m_width(0){};
			~Framebuffer();

			bool InitFramebuffer(int height,int width,GLfloat magFilter,GLfloat minFilter,bool depth = false);

			GLuint m_FBOhandle;
			GLuint m_texHandle;
			GLuint m_depthHandle;
			int m_height;
			int m_width;
	};
};
