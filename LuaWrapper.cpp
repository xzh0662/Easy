/*
 * LuaWrapper.cpp
 *
 *  Created on: Aug 14, 2015
 *      Author: root
 */

#include "LuaWrapper.h"
#include "stdio.h"

static int onError(lua_State *L)
{
	const char *msg = lua_tostring(L, -1);
	if (msg)
		luaL_traceback(L, L, msg, 1);
	else {
		lua_pushliteral(L, "(no error message)");
	}
	return 1;
}

LuaWrapper::LuaWrapper(void)
{
	ls_ = luaL_newstate();
	luaL_openlibs(ls_);
}

LuaWrapper::~LuaWrapper(void)
{
	if (ls_ != 0 )
	{
		lua_close(this->ls_);
	}
}

LuaWrapper* LuaWrapper::instance_ = 0;

LuaWrapper* LuaWrapper::instance(void)
{
    if (instance_ == 0)
    {
        instance_ = new LuaWrapper();
    }
    return instance_;
}

void LuaWrapper::destroy(void)
{
	delete instance_;
}

lua_State * LuaWrapper::luaState(void)
{
	return this->ls_;
}

int LuaWrapper::doString(const char *str)
{
	int top = lua_gettop(ls_);
	lua_pushcfunction(ls_, onError);
	if (luaL_loadstring(ls_, str) != LUA_OK)
	{
		fprintf(stderr,"%s\n",lua_tostring(ls_,-1));
	}
	else
	{
		if (lua_pcall(ls_, 0, 0, top + 1) != LUA_OK)
		{
			fprintf(stderr,"%s\n",lua_tostring(ls_,-1));
		}
	}

	lua_settop(ls_, top);
	return 0;
}

int LuaWrapper::doFile(const char *fileName)
{
	int top = lua_gettop(ls_);
	lua_pushcfunction(ls_, onError);
	if (luaL_loadfile(ls_, fileName) != LUA_OK)
	{
		fprintf(stderr,"%s\n",lua_tostring(ls_,-1));
	}
	else
	{
		if (lua_pcall(ls_, 0, 0, top + 1) != LUA_OK)
		{
			fprintf(stderr,"%s\n",lua_tostring(ls_,-1));
		}
	}
	lua_settop(ls_, top);

	return 0;
}

int LuaWrapper::path(const char *path)
{
	lua_pushstring(ls_, path);
	lua_setglobal(ls_, "LUA_PATH");
	return this->doString("package.path = LUA_PATH");
}

