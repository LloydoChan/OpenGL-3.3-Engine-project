//FullscreenQuad.cpp
//last updata 18/07/2012

#include "Quad.h"

GLfloat fullscreenQuadData[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,

	1.0f,  1.0f, 0.0f,
};

unsigned int quadIndices[] = {
	0,1,2,3
};



bool Quad::Init(float* vertices,bool fullscreen){

	if(fullscreen){
		m_data.Init(quadIndices,4,fullscreenQuadData,NULL,NULL);
	}else{
		m_data.Init(quadIndices,4,vertices,NULL,NULL);
	}

	return true;
}

void Quad::Draw(){
	
	glBindVertexArray(m_data.GetVAO());
	glDrawElements(GL_TRIANGLE_STRIP,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}
