#include "Physics.hpp"

void bindPhysicsToLua(lua_State *state)
{
    ColliderShape::bindLua(state);
    CircleColliderShape::bindLua(state);
    RectangleColliderShape::bindLua(state);
    PhysicsBody::bindLua(state);
    PhysicsWorld::bindLua(state);
}