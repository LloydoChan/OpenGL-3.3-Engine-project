//Script.h - an interface to a LUA script class for fast prototyping etc...
//This code is copyright of Jonathan S. Harbour - this class is part of the 
//"Advanced 2D Game programming" educational book.

#pragma once
#include "Includes.h"
#include <lua.hpp>


namespace OpenGL_3_3Engine
{
	class Script
	{
		public:
			Script();
			Script(const std::string& filename);
			virtual ~Script();

			bool LoadScript(const std::string& scriptFile);
			const std::string GetGlobalString(const std::string& name)const;
			float GetGlobalNumber(const std::string& name)const;
			bool GetGlobalBoolean(const std::string& name)const;

			void SetGlobalString(const std::string& name,const std::string& value);
			void SetGlobalNumber(const std::string& name,float value);
			void SetGlobalBoolean(const std::string& name,bool value);

			void RunFunction(const std::string& name);

			
		private:
			lua_State* luaState;
	};
};