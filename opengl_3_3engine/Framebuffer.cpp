//Framebuffer.cpp
#include "Framebuffer.h"

namespace OpenGL_3_3Engine
{
	Framebuffer::~Framebuffer()
	{
		glDeleteTextures(1, &m_texHandle);
		glDeleteFramebuffers(1, &m_FBOhandle);
		glDeleteRenderbuffers(1, &m_depthHandle);

	}


	bool Framebuffer::InitFramebuffer(int height,int width,GLfloat magFilter,GLfloat minFilter,bool depth)
	{
		m_height = height;
		m_width  = width;
		


		glGenTextures(1,&m_texHandle);
		glBindTexture(GL_TEXTURE_2D,m_texHandle);

		if(!depth)
		{
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,m_width,m_height,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,NULL);
		}

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		

		glGenFramebuffers(1,&m_FBOhandle);
		glBindFramebuffer(GL_FRAMEBUFFER,m_FBOhandle);

		glGenRenderbuffers(1,&m_depthHandle);
		glBindRenderbuffer(GL_RENDERBUFFER,m_depthHandle);

		glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,m_width,m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,m_depthHandle);


		if(!depth)
		{
			glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,m_texHandle,0);
			GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
			glDrawBuffers(1,drawBufs);
		}
		else
		{
			glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,m_texHandle,0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}


		

		 if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		 {
			 std::cout<<"problem with framebuffer!";
			 return false;
		 }
		 else
		 {
			 std::cout<<"framebuffer ok! :)";
		 }

	    glBindFramebuffer(GL_FRAMEBUFFER,0);
		
		return true;
	}
};
