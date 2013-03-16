//ResourceManager.cpp

#ifdef _RESOURCE_MAN_H

template<class T>
ResourceManager<T>::~ResourceManager(){
	EmptyList();
}

template<class T>
T*				ResourceManager<T>::GetElement(const unsigned int handle){
	assert(handle < m_list.size() && "handle is too big");
	return m_list[handle];
}

template<class T>
T*				ResourceManager<T>::GetElement(const string& name,const string& path){

	// Ensure the name and path are valid, and the list is valid and not empty.
	if( name.empty() || path.empty() ||  m_list.empty())
		return NULL;

	string fileName = path+name;
	for(vector<T*>::iterator i = m_list.begin(); i != m_list.end(); i++){
		if((*i) != NULL){
			if((*i)->GetFileName() == fileName){
				return (*i);
			}
		}
	}

	std::cerr<<"the resource "<<name<<" was not found"<<std::endl;
	return NULL;
}

template<class T>
vector<T>*		ResourceManager<T>::GetList(){
	return m_list;
}


template<class T>
T*				ResourceManager<T>::operator[](const unsigned int handle){
    assert(handle <= m_list.size && "invalid handle was passed");
	return m_list[handle];
}

template<class T>
void			ResourceManager<T>::Remove(const unsigned int handle){
	T* res = m_list[handle];

	res->DecRef();

	if(res->GetRefCount() == 0){
	  m_handles.push(handle);
	  delete res;
	  m_list[handle] = NULL;
	}

}

template<class T>
unsigned int	ResourceManager<T>::Add(const string& name,const string& path){

   T* res = GetElement(name,path);
   if(res != NULL){
     res->IncRef();
	 return res->GetResHandle();
   }

   unsigned int handle;
   bool handleAvailable = !m_handles.empty();
   
   if(!handleAvailable){
	   handle = m_list.size();
   }else{
	   handle = m_handles.top();
	   m_handles.pop();
   }

   T* newResource = NULL;

   if(CreateResource!=NULL){
	   CreateResource(&newResource,handle,name,path);
   }else{
	   newResource = new T(handle,name,path);
   }

   if(!handleAvailable){
	  m_list.push_back(newResource);
   }else{
      m_list[handle] = newResource;
   }

   return handle;

}

template<class T>
void			ResourceManager<T>::EmptyList(){
	for(vector<T*>::iterator i = m_list.begin(); i != m_list.end(); i++){
		if((*i) != NULL)
		  delete *i;
	}

	m_list.clear();
}

#endif