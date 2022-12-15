#include "Vector.hpp"
#include <cmath>
#include <fmt/core.h>

void Vector2::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Vector2>("Vector2")
        .addProperty("x", &Vector2::x)
        .addProperty("y", &Vector2::y)
        .addFunction("len", &Vector2::length)
        .addFunction("normalized", &Vector2::normalize)
        .addFunction("__add", &Vector2::add)
        .addFunction("__sub", &Vector2::sub)
        .addFunction("__mul", &Vector2::mul)
        .addFunction("__tostring", &Vector2::toString)
        .addConstructor<void (*)(float, float)>()
        .endClass();
}

float Vector2::length()
{
    return std::sqrt(x * x + y * y);
}
Vector2 Vector2::normalize()
{
    float_t len = length();
    if (len == 0)
    {
        return Vector2(0, 0);
    }
    return Vector2(x / len, y / len);
}

std::string Vector2::toString()
{
    return fmt::format("x: {}, y: {}", x, y);
}

Vector2 Vector2::add(Vector2 const &b)
{
    return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::sub(Vector2 const &b)
{
    return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::mul(float b)
{
    return Vector2(x * b, y * b);
}