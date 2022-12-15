#include "Color.hpp"

void Color::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Color>("Color")
        .addProperty("r", &Color::r)
        .addProperty("g", &Color::g)
        .addProperty("b", &Color::b)
        .addConstructor<void (*)(uint8_t, uint8_t, uint8_t)>()
        .endClass();
}