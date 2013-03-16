//FrameBuffer.cpp
//Last modified 07/01/203

#include "FrameBuffer.h"

void FrameBuffer::Destroy(){
	glDeleteTextures(1,&m_texHandle);
	glDeleteFramebuffers(1,&m_FBOhandle);
	
	if(m_depthHandle != 0){
		glDeleteRenderbuffersEXT(1, &m_depthHandle);
	}

	m_texHandle = 0;
	m_width = 0;
	m_height = 0;}


bool FrameBuffer::InitFramebuffer(int width,int height,GLfloat magFilter,GLfloat minFilter,bool depth){


	m_width = width;
	m_height = height;


	// Texture
	glGenTextures( 1, &m_texHandle);
	glBindTexture(GL_TEXTURE_2D, m_texHandle);
	glTexParameterf(m_texHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(m_texHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_texHandle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(m_texHandle, GL_TEXTURE_WRAP_T, GL_REPEAT);


	if(!depth){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	}else{
		glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,m_width,m_height,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,NULL);
	}

		// Frame buffer
		glGenFramebuffers(1, &m_FBOhandle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBOhandle);
		glGenRenderbuffers(1, &m_depthHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,m_width,m_height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthHandle);
		
		//  attach the framebuffer to our texture, which may be a depth texture
		if(depth) {
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,m_texHandle,0);
			
			//  disable drawing to any buffers, we only want the depth
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}else{
			glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,m_texHandle,0);
			GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
			glDrawBuffers(1,drawBufs);
		}

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
			 std::cout<<"problem with framebuffer!";
			 return false;
		 }else{
			 std::cout<<"framebuffer ok! :)";
		 }

	    glBindFramebuffer(GL_FRAMEBUFFER,0);
		
		return true;
}








