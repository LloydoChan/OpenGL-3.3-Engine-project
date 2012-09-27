//TextureManager.cpp - implementation of the class
//last update : 30/07/2012

#include "TextureManager.h"

namespace OpenGL_3_3Engine
{
	TextureManager::~TextureManager()
	{
		std::cout<<"destructor for tex Man called!"<<std::endl;
		for(std::map<std::string,TextureRecord*>::iterator tex = m_textureMap.begin(); tex != m_textureMap.end();
			tex++)
		{
			m_textureMap.erase(tex++);
		}

	}

	GLuint TextureManager::GetRecord(std::string& id)
	{
		if(m_textureMap.find(id) != m_textureMap.end())
		{
			m_textureMap[id]->refCount++;
			//std::cout<< id <<" already loaded!"<<std::endl;
			return m_textureMap[id]->texData.m_handle;
		}

		TextureRecord* newTexRec = new TextureRecord;

		newTexRec->refCount = 1;
		newTexRec->texData.Init(id.c_str(),GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT);

		m_textureMap[id] = newTexRec;

		return newTexRec->texData.m_handle;
	}

	void TextureManager::Release(std::string& id)
	{
		if(m_textureMap.find(id) != m_textureMap.end())
		{
			if(m_textureMap[id]->refCount == 1)
			{
				m_textureMap.erase(m_textureMap.find(id));
			}
			else
			{
				m_textureMap[id]->refCount++;
			}
		}
	}

};
