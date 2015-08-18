/*
 * LuaWrapper.cpp
 *
 *  Created on: Aug 14, 2015
 *      Author: root
 */

#include "LuaWrapper.h"

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
	int ret = luaL_loadstring(ls_, str);
	if (ret != 0)
	{
		return ret;
	}
	return lua_pcall(ls_, 0, 0, 0);
}

int LuaWrapper::doFile(const char *fileName)
{
	int ret = luaL_loadfile(ls_, fileName);
	if (ret != 0)
	{
		return ret;
	}
	return lua_pcall(ls_, 0, 0, 0);

}

