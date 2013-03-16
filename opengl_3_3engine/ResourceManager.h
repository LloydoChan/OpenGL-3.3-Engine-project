//ResourceManager.h
#ifndef _RESOURCE_MAN_H
#define _RESOURCE_MAN_H

#include "Includes.h"

using std::vector;
using std::stack;
using std::string;

class Texture;
class Shader;


template <class T>
class ResourceManager{
	public:
		ResourceManager(void(*CreateResourceFunc)(T**,const unsigned int,const std::string&,const std::string&))
						{CreateResource = CreateResourceFunc;}
		~ResourceManager();

		T*				GetElement(const unsigned int handle);
		T*				GetElement(const string& name,const string& path);
		vector<T>*		GetList();

		T*				operator[](const unsigned int handle);
		void			Remove(const unsigned int handle);
		unsigned int	Add(const string& name,const string& path);
		void			EmptyList();

		void			ChangeResourceCreation(void(*CreateResourceFunc)(T**,const unsigned int,const std::string&,const std::string&))
		{
			CreateResource = CreateResourceFunc;
		}
	private:
		vector<T*>																m_list;
		stack<unsigned int>														m_handles;
		void(*CreateResource)(T**,const unsigned int,const std::string&,const std::string&);

};

#include "ResourceManager.cpp"


#endif