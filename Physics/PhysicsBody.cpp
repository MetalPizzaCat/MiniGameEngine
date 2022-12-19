#include "PhysicsBody.hpp"

void PhysicsBody::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsBody>("Body")
        .addFunction("get_position", &PhysicsBody::getPosition)
        .addConstructor<void (*)(PhysicsWorld *, Vector2, ColliderShape const &, int)>()
        .endClass()
        .endNamespace();
}
Vector2 PhysicsBody::getPosition() const
{
    return Vector2(m_body->GetPosition().x * m_world->getWorldScale(), m_body->GetPosition().y * m_world->getWorldScale());
}
