#include "ColliderShape.hpp"

void ColliderShape::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<ColliderShape>("ColliderShape")
        .endClass()
        .endNamespace();
}

void CircleColliderShape::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .deriveClass<CircleColliderShape, ColliderShape>("CircleColliderShape")
        .addConstructor<void (*)(PhysicsWorld *, float)>()
        .endClass()
        .endNamespace();
}

void RectangleColliderShape::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .deriveClass<RectangleColliderShape, ColliderShape>("RectangleColliderShape")
        .addConstructor<void (*)(PhysicsWorld *, float, float)>()
        .endClass()
        .endNamespace();
}