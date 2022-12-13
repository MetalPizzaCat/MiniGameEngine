#include "Vector.hpp"

void LuaBind::bindVector(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Vector2>("Vector2")
        .addProperty("x", &Vector2::x)
        .addProperty("y", &Vector2::y)
        .addConstructor<void (*)(float, float)>()
        .endClass();
}