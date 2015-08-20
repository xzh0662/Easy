/*
 * LuaWrapper.h
 *
 *  Created on: Aug 14, 2015
 *      Author: root
 */

#ifndef LUAWRAPPER_H_
#define LUAWRAPPER_H_
extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

class LuaWrapper
{
private:
	LuaWrapper(void);
	virtual ~LuaWrapper(void);
public:
	static LuaWrapper* instance(void);
	static void destroy(void);

	lua_State * luaState(void);

	int doString(const char *str);
	int doFile(const char *fileName);
	int path(const char *path);

private:
	static LuaWrapper* instance_;

	lua_State * ls_;
};

#define LUA_WRAPPER LuaWrapper::instance()



#endif /* LUAWRAPPER_H_ */
