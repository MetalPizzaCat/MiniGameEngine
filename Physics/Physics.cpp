#include "Physics.hpp"

void bindPhysicsToLua(lua_State *state)
{
    ColliderShape::bindLua(state);
    CircleColliderShape::bindLua(state);
    RectangleColliderShape::bindLua(state);
    PhysicsBodyDefintion::bindLua(state);
    PhysicsBody::bindLua(state);
    PhysicsWorld::bindLua(state);
}