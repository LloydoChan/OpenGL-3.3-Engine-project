//FullscreenQuad.h - simple full screen quad used for post processing etc
//last update 18/07/2012
#pragma once
#include "Includes.h"
#include "ObjectData.h"



const GLfloat g_quad_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,

	1.0f,  1.0f, 0.0f,
};

const unsigned int quad_indices[] = {
	0,1,2,3
};

class FullscreenQuad
{
	public:
		FullscreenQuad();
		~FullscreenQuad(){};

		bool				Init();
		void				Draw();

  private:
		ObjectData			m_data;
};
