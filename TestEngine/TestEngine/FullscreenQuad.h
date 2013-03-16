//FullscreenQuad.h
//last update 18/07/2012
#pragma once
#include "..\..\OpenGL_3_3Engine\OpenGL_3_3Engine.h"


namespace OpenGL_3_3Engine
{
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

			bool Init();
			void Draw();

			ObjectData m_data;
	};
}