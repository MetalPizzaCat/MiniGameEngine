#include "Vector.hpp"

void Vector2::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Vector2>("Vector2")
        .addProperty("x", &Vector2::x)
        .addProperty("y", &Vector2::y)
        .addConstructor<void (*)(float, float)>()
        .endClass();
}