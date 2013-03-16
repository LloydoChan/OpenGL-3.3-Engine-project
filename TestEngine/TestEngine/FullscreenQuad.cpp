//FullscreenQuad.cpp
//last updata 18/07/2012

#include "FullscreenQuad.h"


namespace OpenGL_3_3Engine
{
	FullscreenQuad::FullscreenQuad():m_data(1,2)
	{
	}

	bool FullscreenQuad::Init()
	{
		m_data.Init(quad_indices,sizeof(g_quad_vertex_buffer_data),g_quad_vertex_buffer_data,NULL,NULL);

		return true;
	}

	void FullscreenQuad::Draw()
	{
		glBindVertexArray(m_data.GetVAO());
		glDrawElements(GL_TRIANGLE_STRIP,6,GL_UNSIGNED_INT,0);
	}
}