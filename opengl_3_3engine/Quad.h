//Quad.h - quad class used for full screen quads and big planes etc
//last update 24/01/2012
#pragma once
#include "Includes.h"
#include "ObjectData.h"
#include "Shader.h"




class Quad
{
	public:
		Quad():m_data(1,2){};
		~Quad(){};

		bool				Init(float* vertices,bool fullscreen = false);
		void				Draw();

  private:
		ObjectData			m_data;
};
