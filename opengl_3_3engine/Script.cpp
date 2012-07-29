//script.cpp
#include "Script.h"

namespace OpenGL_3_3Engine
{
	Script::Script()
	{
		luaState = lua_open();
		luaL_openlibs(luaState);
	}

	Script::Script(const std::string& scriptFile) 
	{
		Script();
		LoadScript(scriptFile);
	}

	Script::~Script()
	{
		lua_close(luaState);
	}

	bool Script::LoadScript(const std::string& scriptFile)
	{
		bool value = true;
		try
		{
			luaL_dofile(luaState,scriptFile.c_str());
		}
		catch(...)
		{
			value = false;
		}

		return value;
	}

	const std::string Script::GetGlobalString(const std::string& name)const
	{
		std::string value = "";
		try
		{
			lua_getglobal(luaState,name.c_str());
			value = lua_tostring(luaState,-1);
			lua_pop(luaState,1);
		}
		catch(...)
		{
		}
		return value;
	}

	void Script::SetGlobalString(const std::string& name,const std::string& value)
	{
		lua_pushstring(luaState,value.c_str());
		lua_setglobal(luaState,name.c_str());
	}

	float Script::GetGlobalNumber(const std::string& name)const
	{
		float value = 0.0f;
		try
		{
			lua_getglobal(luaState,name.c_str());
			value = lua_tonumber(luaState,-1);
			lua_pop(luaState,1);
		}
		catch(...)
		{
		}
		return value;
	}

	void Script::SetGlobalNumber(const std::string& name,float value)
	{
		lua_pushnumber(luaState,value);
		lua_setglobal(luaState,name.c_str());
	}

	bool Script::GetGlobalBoolean(const std::string& name)const
	{
		bool value = 0;
		try
		{
			lua_getglobal(luaState,name.c_str());
			value =(bool)(int)lua_toboolean(luaState,-1);
			lua_pop(luaState,1);
		}
		catch(...)
		{
		}
		return value;
	}

	void Script::SetGlobalBoolean(const std::string& name,bool value)
	{
		lua_pushboolean(luaState,(int)value);
		lua_setglobal(luaState,name.c_str());
	}

	void Script::RunFunction(const std::string& name)
	{
		lua_getglobal(luaState,name.c_str());
		lua_call(luaState,0,0);
	}
};