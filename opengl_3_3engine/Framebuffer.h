//FrameBufferObject.h - a framebuffer object class used for rendering to a texture for all kinds of effects!
//Last modified 07/01/2013



#pragma once

#include "Includes.h"


class FrameBuffer : public Uncopyable
{

  public:
	FrameBuffer():m_FBOhandle(0),m_texHandle(0),m_depthHandle(0),m_height(0),m_width(0){};
	~FrameBuffer() {Destroy();}

	bool				InitFramebuffer(int width,int height,GLfloat magFilter,GLfloat minFilter,bool depth = false);
	void				Destroy();

	GLuint				GetTextureHandle() const	{return m_texHandle;} 
	GLuint				GetFrameBufferHandle() const {return m_FBOhandle;}
    GLuint				GetWidth() const	{return m_width;}
	GLuint				GetHeight() const {return m_height;}

private:
	GLuint				m_FBOhandle;
	GLuint				m_texHandle;
	GLuint				m_depthHandle;
	int					m_height;
	int					m_width;
	
};




