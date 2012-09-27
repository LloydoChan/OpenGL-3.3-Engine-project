//TextureManager.h - a manager class for the textures in the game - prevents loading textures multiple times
//by meshes, providing handles to the objects that need to bind a texture and indexing into a std::map by
//using the filename as an index. It explicitly calls the constructor of the Texture class for each new texture
//using reference counting textures are deleted if the ref count goes to 0. If an external class calls for the 
//relevent handle it is incremented by 1.
//If this kind of class inherited from an ADT to allow passing of an abstract type pointer to many different classes
//that would be plain lazy and rear the ugly head of general 'OOP bullshit' as coined by Mike Acton. HOWEVER
//unlike him I don't think references are 'pointless cruft'.

//last update 30/07/2012

#pragma once
#include "Includes.h"
#include "Texture.h"

namespace OpenGL_3_3Engine
{
	class TextureManager
	{
		public:
			TextureManager(){};
			~TextureManager();

			GLuint GetRecord(std::string& id);
			void   Release(std::string& id);
		private:
			
			struct TextureRecord
			{
				int refCount;
				Texture texData;
			};

			std::map<std::string,TextureRecord*> m_textureMap;

			//make the assignment op and copy constructor private to make it
			//idiot proof, namely from myself

			TextureManager& operator=(TextureManager& rhs);
			TextureManager(TextureManager& rhs);
	};
};