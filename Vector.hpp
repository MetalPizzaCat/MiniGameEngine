#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>

struct Vector2
{
    float x;
    float y;

    Vector2(float x, float y) : x(x), y(y) {}

    static void bindLua(lua_State *state);
};