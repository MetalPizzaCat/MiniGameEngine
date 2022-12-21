#pragma once
#include "PhysicsWorld.hpp"
#include "ColliderShape.hpp"
#include "../Lua/LuaMachine.hpp"

/// @brief Class that represents a body in a physical world
class PhysicsBody
{
public:
    PhysicsBody(PhysicsWorld *world,
                Vector2 position,
                ColliderShape const &shape,
                int type,
                luabridge::LuaRef contactBeginCallback,
                luabridge::LuaRef contactEndCallback,
                luabridge::LuaRef data) : m_world(world),
                                          m_contactBeginCallback(contactBeginCallback),
                                          m_contactEndCallback(contactEndCallback),
                                          m_data(data)
    {
        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)type;
        bodyDef.position.Set(position.x / PHYSICS_SCALE, position.y / PHYSICS_SCALE);
        m_body = m_world->getWorld()->CreateBody(&bodyDef);

        m_body->CreateFixture(shape.getFixtureDef());
        m_body->SetUserData(this);
    }

    /// @brief Get current location of the body in the physics world
    /// @return current location
    Vector2 getPosition() const;

    Vector2 getVelocity() const;

    void setVelocity(Vector2 const &velocity);

    /// @brief Current rotation in radians
    /// @return  Current rotation in radians
    float getRotation() const;

    /// @brief Called when contact between this and other body happens
    /// @param other Body with which this body collided
    void BeginContact(PhysicsBody *other);

    /// @brief Called when contact between this and other body end
    /// @param other Body with which this body collided
    void EndContact(PhysicsBody *other);

    /// @brief Sets body to inactive
    void setIsActive(bool active)
    {
        m_body->SetActive(active);
    }

    bool getIsActive() const { return m_body->IsActive(); }

    ~PhysicsBody()
    {
        m_world->getWorld()->DestroyBody(m_body);
    }

    static void bindLua(lua_State *state);

private:
    PhysicsWorld *m_world;
    b2Body *m_body;
    luabridge::LuaRef m_contactBeginCallback;
    luabridge::LuaRef m_contactEndCallback;
    luabridge::LuaRef m_data;
};