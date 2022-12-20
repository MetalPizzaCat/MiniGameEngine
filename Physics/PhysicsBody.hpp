#pragma once
#include "PhysicsWorld.hpp"
#include "ColliderShape.hpp"

class PhysicsBody
{
public:
    PhysicsBody(PhysicsWorld *world, Vector2 position, ColliderShape const &shape, int type) : m_world(world)
    {
        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)type;
        bodyDef.position.Set(position.x / PHYSICS_SCALE, position.y / PHYSICS_SCALE);
        m_body = m_world->getWorld()->CreateBody(&bodyDef);

        m_body->CreateFixture(shape.getFixtureDef());
    }

    /// @brief Get current location of the body in the physics world
    /// @return current location
    Vector2 getPosition() const;

    Vector2 getVelocity() const;

    void setVelocity(Vector2 const& velocity);

    /// @brief Current rotation in radians
    /// @return  Current rotation in radians
    float getRotation() const;

    ~PhysicsBody()
    {
        m_world->getWorld()->DestroyBody(m_body);
    }

    static void bindLua(lua_State *state);

private:
    PhysicsWorld *m_world;
    b2Body *m_body;
};