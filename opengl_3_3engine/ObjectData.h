//ObjectInfo.h
//last updated 24/07/2012
#pragma once
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	class ObjectData
	{
		public:

			//ObjectData constructor - takes the number of VBO objects needed, eg 3 for vertices, normals
			//and texture co ordintates, and a number of triangle faces to render
			ObjectData(int numVBObjects,int numFaces) : m_numVbos(numVBObjects), m_numFaces(numFaces){};
			~ObjectData();


			//bool Init(int numVertices,...) takes a number of vertices for the objectdata to hold
			//and a variable number of arguments that should be passed in the format data, components
			//where data is the pointer to the data and components represents the number of elems in each
			//vertex, e.g 3 for a normal, 4 for a normalised vertex, x for number of bones etc

			//so a call like Init(indices,30,vertices,3) creates an index buffer and uses the data in vertices
			//and knows there are 30 vertices and 3 components in each vertex

			bool Init(const unsigned int* indices,int numVertices,...);
			
			GLuint GetVAO()const {return m_vao;}
			GLuint GetNumFaces()const {return m_numFaces;}

		private:
			bool BindData(GLuint buffer,int numComponents,int numVertices,float* data);
			bool BindVAO();

			//make assignment and copy constructor private
			ObjectData(const ObjectData& rhs);
			ObjectData& operator=(const ObjectData& rhs);

			GLuint* m_vbos;
			GLint* m_numComponents;
			GLuint m_vao;
			GLuint m_indexBuff;
			GLuint m_numVbos;
			GLuint m_numFaces;
	};

};