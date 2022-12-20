#include "PhysicsWorld.hpp"

b2Vec2 PhysicsHelpers::fromVector2(Vector2 const &vec) { return b2Vec2(vec.x, vec.y); }

void PhysicsWorld::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsWorld>("World")
        .addProperty("gravity", &PhysicsWorld::getGravity, &PhysicsWorld::setGravity)
        .endClass()
        .endNamespace();
}

void PhysicsWorld::step(float32 timeStep)
{
    m_world->Step(timeStep, m_velocityIterCount, m_positionIterCount);
}

void PhysicsWorld::setDebugDraw(b2Draw *debug)
{
    m_world->SetDebugDraw(debug);
}

Vector2 PhysicsWorld::getGravity() const
{
    return Vector2(m_world->GetGravity().x, m_world->GetGravity().y);
}

void PhysicsWorld::setGravity(Vector2 const &gravity)
{
    m_world->SetGravity(PhysicsHelpers::fromVector2(gravity));
}
