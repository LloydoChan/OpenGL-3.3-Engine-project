//Framebuffer.h
#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	class Framebuffer
	{
		public:
			Framebuffer(){};
			~Framebuffer();

			bool InitFramebuffer(int height,int width,GLfloat magFilter,GLfloat minFilter,bool depth = false);

			GLuint m_FBOhandle;
			GLuint m_texHandle;
			GLuint m_depthHandle;
			int m_height;
			int m_width;
	};
};
