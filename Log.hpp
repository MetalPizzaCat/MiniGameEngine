#pragma once
#include <string>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
namespace Log
{
    void error(std::string error);
    void print(std::string info);
    void info(std::string info);
    void bindLua(lua_State *state);
}