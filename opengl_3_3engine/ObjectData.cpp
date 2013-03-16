//ObjectData.cpp
//last updated 24/07/2012
#include "ObjectData.h"


ObjectData::~ObjectData(){
	glDeleteBuffers(m_numVbos,m_vbos);
	glDeleteVertexArrays(1,&m_vao);
	delete [] m_vertexInfo;
	delete [] m_normalInfo;
	delete [] m_textureInfo;
	delete [] m_vbos;
}

bool ObjectData::Init(const unsigned int* indices,unsigned int numVertices,float* vertices,float* normals,float* textures){
	m_vbos = new GLuint[m_numVbos];

	if(indices){
		//generate an index buffer if required
		glGenBuffers(1,&m_indexBuff);

		//get info for num of faces and the index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numFaces * 3, indices, GL_STATIC_DRAW);
	}

	
	//generate info for the buffers
	glGenBuffers(m_numVbos,m_vbos);

	m_numComponents = new unsigned int[m_numVbos];

	int buffer = 0;
	glBindBuffer(GL_ARRAY_BUFFER,m_vbos[buffer]);
	glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(float) * 3,vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	m_numComponents[buffer++] = 3; 

	m_vertexInfo = new vec3[numVertices];

	for(unsigned int vertex = 0; vertex < numVertices;vertex++){
			memcpy(&m_vertexInfo[vertex],&vertices[vertex*3],sizeof(float) * 3);
			
	}

	if(normals){
		glBindBuffer(GL_ARRAY_BUFFER,m_vbos[buffer]);
		glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(float) * 3,normals,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		m_numComponents[buffer++] = 3; 


		m_normalInfo = new vec3[numVertices];
		for(unsigned int vertex = 0; vertex < numVertices;vertex++){
			memcpy(&m_normalInfo[vertex],&normals[vertex*3],sizeof(float) * 3);
		}
	}

	if(textures){
		glBindBuffer(GL_ARRAY_BUFFER,m_vbos[buffer]);
		glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(float) * 2,textures,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		m_numComponents[buffer] = 2; 

		m_textureInfo = new vec2[numVertices];

		for(unsigned int vertex = 0; vertex < numVertices;vertex++){
			memcpy(&m_textureInfo[vertex],&textures[vertex*2],sizeof(float) * 2);
		}
	}

	if(indices){
		BindVAO(true);
	}else{
		BindVAO(false);
	}
	return true;
}

bool ObjectData::InitInterleaved(const unsigned int* indices,unsigned int numVertices,float* vertices,
	                             float* normals,float* textures){
	m_vbos = new GLuint[1];

	//due to variable num of args, need to use va_list and va_arg to access the data
	va_list attribList;
	va_start(attribList,numVertices);

	if(indices){
		//generate an index buffer if required
		glGenBuffers(1,&m_indexBuff);

		//get info for num of faces and the index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numFaces * 3, indices, GL_STATIC_DRAW);
	}

	
	//generate info for the buffers
	glGenBuffers(1,m_vbos);


	float** data = new float*[m_numVbos];

	int total = 0;

	for(GLuint component = 0; component < m_numVbos; component++)
	{
		data[component]				= va_arg(attribList,float*);
	}

	GLenum error = glGetError();
	glBindBuffer(GL_ARRAY_BUFFER,m_vbos[0]);
	error = glGetError();
	int offset = 0;

	/*for(int component = 0; component < m_numVbos; component++)
	{
		m_sizes[component] = numVertices * sizeof(float) * m_numComponents[component];
		glBufferSubData(GL_ARRAY_BUFFER, offset,m_sizes[component],data[component]);
		offset += m_sizes[component] ;
	}*/
	GLfloat* interleavedData = new GLfloat[numVertices * (m_numVbos * 4)];

	int bufferOffset = 0;
	//copy the data
	for(unsigned int vertex = 0; vertex < numVertices; vertex++){
		for(unsigned int buffer = 0; buffer < m_numVbos; buffer++){
			for(int comp = 0; comp < 4; comp++){
				int index1 = vertex * 4 + comp;
				int index2 = vertex * (m_numVbos * 4) + buffer * 4 + comp;
				float value = data[buffer][index1];
				interleavedData[index2] = value;
			}
		}
	}

	glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(float) * total,interleavedData,GL_STATIC_DRAW);

	delete [] interleavedData;

	error = glGetError();

	glBindBuffer(GL_ARRAY_BUFFER,0);
	

	if(indices){
		BindInterleavedVAO(true,total);
	}else{
		BindInterleavedVAO(false,total);
	}
	return true;
}



bool ObjectData::BindVAO(bool indices){

	glGenVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	if(indices)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);

	for(unsigned int buffer = 0; buffer < m_numVbos; buffer++){
		glEnableVertexAttribArray(buffer);
		glBindBuffer(GL_ARRAY_BUFFER,m_vbos[buffer]);
		glVertexAttribPointer(buffer,m_numComponents[buffer],GL_FLOAT,GL_FALSE,0,(GLubyte*)NULL);
	}

	glBindVertexArray(0);

	if(indices)
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}

bool ObjectData::BindInterleavedVAO(bool indices,int total){
	glGenVertexArrays(1,&m_vao);
	glBindVertexArray(m_vao);

	if(indices)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);

	
	glBindBuffer(GL_ARRAY_BUFFER,m_vbos[0]);

	int bufferOffset = 0;

	for(unsigned int buffer = 0; buffer < m_numVbos; buffer++){
		glEnableVertexAttribArray(buffer);
		if(buffer > 0){
			glVertexAttribPointer(buffer,4,GL_FLOAT,GL_FALSE,16 * m_numVbos,(GLubyte*)( 16 * buffer));
		}else{
			glVertexAttribPointer(buffer,4,GL_FLOAT,GL_FALSE,16 * m_numVbos,0);
		}
	
	}

	glBindVertexArray(0);

	if(indices)
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return true;
}


