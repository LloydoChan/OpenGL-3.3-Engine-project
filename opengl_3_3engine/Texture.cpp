//Texture.cpp
//Last updated: 17/07/2012

#include "Texture.h"
#include "ImageUtils.h"

//bool Texture::Init(const char* filename,GLfloat magFilter,GLfloat minFilter,GLfloat sWrap,GLfloat tWrap)
//takes care of all the nitty gritty texture initialisation - binding, generating, etc

bool Texture::Init(){

	glGenTextures(1,&m_textureHandle);
	glBindTexture(GL_TEXTURE_2D,m_textureHandle);

	//use dEvil to load textures now...ALSO CHANGE FUNC TO INCLUDE MIPMAPS BEING SET!

	unsigned int width,height,bytes;
	GLubyte* data = OpenImage(m_fileName.c_str(),width,height,bytes);

	GLint format;

	switch(bytes)
	{
		case 1 :
			format = GL_LUMINANCE;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
	}
	
	glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);

	delete [] data;

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	
	glBindTexture(GL_TEXTURE_2D,0);

	return true;
}

void Texture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D,m_textureHandle);
}

void Texture::Unbind(GLenum textureUnit){
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

	
void CreateTexture(Texture** texture,const unsigned int handle,const std::string& name,const std::string& path){
	*texture = new Texture(handle,name,path); 
	(*texture)->Init();
}