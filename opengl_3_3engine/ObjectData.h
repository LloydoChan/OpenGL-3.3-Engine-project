//ObjectInfo.h
//last updated 24/07/2012
#pragma once
#include "Includes.h"

using glm::vec3;
using glm::vec2;

class ObjectData : public Uncopyable{
	public:

		//ObjectData constructor - takes the number of VBO objects needed, eg 3 for vertices, normals
		//and texture co ordintates, and a number of triangle faces to render
		ObjectData(unsigned int numVBObjects,unsigned int numFaces) : m_numVbos(numVBObjects), m_numFaces(numFaces),m_vertexInfo(NULL),
		m_normalInfo(NULL),m_textureInfo(NULL),m_numComponents(NULL){};

		~ObjectData();

		bool				Init(const unsigned int* indices,unsigned int numVertices,float* vertices,float* normals,float* textures);
		bool				InitInterleaved(const unsigned int* indices,unsigned int numVertices,float* vertices,float* normals,float* textures);
		GLuint				GetVAO()const {return m_vao;}
		GLuint				GetNumFaces()const {return m_numFaces;}
		GLuint				GetVBO(unsigned int index)const {assert(index<m_numVbos); return m_vbos[index];}
		const vec3*			GetVertices()const {return m_vertexInfo;}

	private:
		bool				BindVAO(bool indices);
		bool				BindInterleavedVAO(bool indices,int total);

		GLuint*				m_vbos;
		GLuint				m_vao;
		GLuint				m_indexBuff;
		unsigned int*		m_numComponents;
		unsigned int  		m_numVbos;
		unsigned int 		m_numFaces;
		vec3*				m_vertexInfo;
		vec3*				m_normalInfo;
		vec2*				m_textureInfo;};

