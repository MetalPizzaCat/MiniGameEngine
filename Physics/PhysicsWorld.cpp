#include "PhysicsWorld.hpp"
#include "../Log.hpp"
#include <algorithm>

b2Vec2 PhysicsHelpers::fromVector2(Vector2 const &vec) { return b2Vec2(vec.x, vec.y); }

void PhysicsWorld::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsWorld>("World")
        .addProperty("gravity", &PhysicsWorld::getGravity, &PhysicsWorld::setGravity)
        .addFunction("create_body", &PhysicsWorld::createBody)
        .endClass()
        .endNamespace();
}

void PhysicsWorld::freeBodies()
{
    if (m_world->IsLocked())
    {
        Log::error("Attempted to perform body destruction while world was locked");
        return;
    }
    for (b2Body *body : m_deadBodies)
    {
        m_world->DestroyBody(body);
    }
    m_deadBodies.clear();
}

PhysicsBody *PhysicsWorld::createBody(Vector2 position, ColliderShape const &shape, int32_t type, luabridge::LuaRef contactBeginCallback, luabridge::LuaRef contactEndCallback, luabridge::LuaRef data)
{
    PhysicsBody *body = new PhysicsBody(this, position, shape, type, contactBeginCallback, contactEndCallback, data);
    m_bodies.push_back(body);
    return body;
}

void PhysicsWorld::destroyBody(PhysicsBody *body)
{
    m_deadBodies.push_back(body->getBody());
    if (std::vector<PhysicsBody *>::iterator it = std::find(m_bodies.begin(), m_bodies.end(), body);
        it != m_bodies.end())
    {
        m_bodies.erase(it);
    }
}

void PhysicsWorld::step(float32 timeStep)
{
    m_world->Step(timeStep, m_velocityIterCount, m_positionIterCount);
    freeBodies();
    for (PhysicsBody *body : m_bodies)
    {
        body->update();
    }
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
