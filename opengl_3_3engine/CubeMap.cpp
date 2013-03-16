//CubeMap.h - Added from previous engine experiment
//LAST MODIFIED 06/01/2012
#include "CubeMap.h"
#include "ImageUtils.h"

namespace OpenGL_3_3Engine{

bool CubeMap::Init(const char* filename){
	glGenTextures(1,&m_handle);
	//glEnable(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);

	const char* suffixes[] = {"positive_x","negative_x","positive_y","negative_y","positive_z","negative_z"};

	GLuint targets[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

	for(int side = 0; side < 6; side++){
		std::string texName = std::string(filename) + "_" +  suffixes[side] + ".jpg";
		unsigned int width,height,bytes;
		GLubyte* data = OpenImage(texName.c_str(),width,height,bytes);

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

		GLenum err = glGetError();
		glTexImage2D(targets[side],0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
		delete [] data;
		//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, img.Width, img.Height, GL_RGB, GL_UNSIGNED_BYTE, img.Data );
		err = glGetError();
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
	return true;
}

};
