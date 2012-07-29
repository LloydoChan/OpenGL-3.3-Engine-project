//ObjectData.cpp
//last updated 24/07/2012
#include "ObjectData.h"

namespace OpenGL_3_3Engine
{
	ObjectData::~ObjectData()
	{
		glDeleteBuffers(m_numVbos,m_vbos);
		glDeleteVertexArrays(1,&m_vao);

		delete [] m_vbos;
		delete [] m_numComponents;
	}

	bool ObjectData::Init(const unsigned int* indices,int numVertices,...)
	{
		m_vbos = new GLuint[m_numVbos];
		m_numComponents = new GLint[m_numVbos];

		//due to variable num of args, need to use va_list and va_arg to access the data
		va_list attribList;
		va_start(attribList,numVertices);

		//generate an index buffer
		glGenBuffers(1,&m_indexBuff);

		//get info for num of faces and the index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numFaces * 3, indices, GL_STATIC_DRAW);

		//generate info for the buffers
		glGenBuffers(m_numVbos,m_vbos);

		
		for(int buffer = 0; buffer < m_numVbos; buffer++)
		{
			float* data				= va_arg(attribList,float*);
			int    numComponents	= va_arg(attribList,int);
			m_numComponents[buffer] = numComponents;
			BindData(m_vbos[buffer],numComponents,numVertices,data);
			

		}

		BindVAO();

		return true;
	}

	bool ObjectData::BindData(GLuint buffer,int numComponents,int numVertices, float* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER,buffer);
		glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(float) * numComponents,data,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);

		return true;
	}

	bool ObjectData::BindVAO()
	{
		glGenVertexArrays(1,&m_vao);
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuff);

		for(int buffer = 0; buffer < m_numVbos; buffer++)
		{
			glEnableVertexAttribArray(buffer);
			glBindBuffer(GL_ARRAY_BUFFER,m_vbos[buffer]);
			glVertexAttribPointer(buffer,m_numComponents[buffer],GL_FLOAT,GL_FALSE,0,(GLubyte*)NULL);
		}


		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		return true;
	}
};