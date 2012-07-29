//ResourceManager.h - interface file for a resource manager class. This class is templatized and used to manage
//various things like textures, shaders, objects, etc!
#include "Includes.h"

namespace OpenGL_3_3Engine
{
	template<class T>
	class ResourceManager
	{
		public:
			ResourceManager(){};
			~ResourceManager(){resources.clear();}

			void AddEntry(const std::string& key,T* entry);

			T*   GetEntry(const std::string& entry);

		private:
			std::map<std::string,T*> resources;
	};

	template <class T>
	void ResourceManager<T>::AddEntry(const std::string& key,T* entry)
	{
		    assert(!resources[key] && "this has already been loaded to the map");
			resources[key] = entry;
		
	}


	template <class T>
	T*   ResourceManager<T>::GetEntry(const std::string& entry)
	{
	
		return resources[entry];
		
	}
};