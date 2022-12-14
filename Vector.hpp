#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
#include <cstddef>

struct Vector2
{
    float x;
    float y;

    Vector2(float x, float y) : x(x), y(y) {}
    Vector2 normalize();
    Vector2 add(Vector2 b);
    std::string toString();
    float length();
    static void bindLua(lua_State *state);
};