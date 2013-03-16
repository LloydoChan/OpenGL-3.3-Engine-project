//Texture.h - texture class - taken from last engine experiment project
//last update 01/11/2013
#pragma once

#include "Includes.h"
#include "Resource.h"



class Texture: public Resource{
	public:
		Texture(const unsigned int handle,const string& name,const string& path) : Resource(handle,name,path) {};
		~Texture(){glDeleteTextures(1,&m_textureHandle);}

		GLuint GetHandle()const {return m_textureHandle;}

		bool Init();
		void Bind(GLenum textureUnit);
		void Unbind(GLenum textureUnit);

    private:
		GLuint m_textureHandle;};

void CreateTexture(Texture** texture,const unsigned int handle,const std::string& path,const std::string& name);