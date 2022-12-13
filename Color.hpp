#pragma once
#include <cstddef>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), b(b), g(g) {}
};

namespace LuaBind
{
    void bindColor(lua_State *state);
}