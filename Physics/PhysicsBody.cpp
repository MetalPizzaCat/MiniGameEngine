#include "PhysicsBody.hpp"
#include "PhysicsWorld.hpp"

void PhysicsBody::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsBody>("Body")
        .addFunction("get_position", &PhysicsBody::getPosition)
        .addFunction("get_rotation", &PhysicsBody::getRotation)
        .addProperty("velocity", &PhysicsBody::getVelocity, &PhysicsBody::setVelocity)
        .addConstructor<void (*)(PhysicsWorld *, Vector2, ColliderShape const &, int)>()
        .endClass()
        .endNamespace();
}
Vector2 PhysicsBody::getPosition() const
{
    return Vector2(m_body->GetPosition().x * m_world->getWorldScale(), m_body->GetPosition().y * m_world->getWorldScale());
}

float PhysicsBody::getRotation() const
{
    return m_body->GetAngle();
}

Vector2 PhysicsBody::getVelocity() const
{
    return Vector2(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
}

void PhysicsBody::setVelocity(Vector2 const& velocity)
{
    m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}