//Resource.h - interface for all resources to be loaded by resource manager
#pragma once
#include "Includes.h"

using std::string;

class Resource{
	public:
		Resource(const unsigned int handle,const string& name,const string& path) : m_handle(handle),
		m_name(name),m_path(path),m_fileName(path+name),m_refCount(0){};
		~Resource(){}

		void DecRef() {m_refCount--;}
		void IncRef() {m_refCount++;}

		unsigned long GetRefCount()const {return m_refCount;}
		unsigned int  GetResHandle()const   {return m_handle;}
		const string& GetPath()const	 {return m_path;}
		const string& GetName()const	 {return m_name;}
		const string& GetFileName()const  {return m_fileName;}
	protected:
		string			m_fileName;
		unsigned int	m_handle;
		string			m_name;
		string			m_path;
		unsigned long	m_refCount;
};