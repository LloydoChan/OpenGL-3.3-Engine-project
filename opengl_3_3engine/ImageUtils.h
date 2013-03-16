//ImageUtils - a simple series of functions to help with loading images
//for textures, cubemaps etc
//LAST MODIFIED 20/01/2013
#pragma once
#include "Includes.h"

GLubyte* OpenImage(const char* filename, unsigned int& width, unsigned int& height, unsigned int& bytes);

void CreateNormalMap(const char* filename,GLuint& texHandle);
