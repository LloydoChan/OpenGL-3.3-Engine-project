//ImageUtils.cpp
#include "ImageUtils.h"


GLubyte* OpenImage(const char* filename, unsigned int& width, unsigned int& height, unsigned int& bytes)
{
	
    // Generate a new texture like in opengl
    ILuint ilTexture;
    ilGenImages(1, &ilTexture);
    ilBindImage(ilTexture);

	

    // Chargement de l'image
	ilLoadImage(filename);


   //get image info - width height and bytes per pixel
	width   = ilGetInteger(IL_IMAGE_WIDTH);
	height  = ilGetInteger(IL_IMAGE_HEIGHT);
	bytes   = ilGetInteger(IL_IMAGE_BPP);

	//if the image has an alpha channel...
	if(bytes==4)
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    //get the image info and copy over to the img pointer to return to the app
    const unsigned char* Pixels = ilGetData();

	GLubyte* img = new GLubyte[width * height * bytes];
	memcpy(img, Pixels,width * height * bytes);

    //now unbind and delete orig info....
    ilBindImage(0);
    ilDeleteImages(1, &ilTexture);

	return img;
}
