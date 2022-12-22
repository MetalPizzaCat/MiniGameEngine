#pragma once
// #include "PhysicsWorld.hpp"
#include "ColliderShape.hpp"
#include "../Graphics/Vector.hpp"
#include "../Lua/LuaMachine.hpp"

class PhysicsWorld;
/// @brief Class that represents a body in a physical world
class PhysicsBody
{
public:
    enum class Type : int32_t
    {
        Static = b2BodyType::b2_staticBody,
        Kinematic = b2BodyType::b2_kinematicBody,
        Dynamic = b2BodyType::b2_dynamicBody
    };

    /// @brief Creates physics body object
    /// @param position Where will the body be spawned
    /// @param shape Shape of the body
    /// @param type Type of the body. See PhysicsBody::Type enum
    /// @param contactBeginCallback Lua function that will be called when this body collides
    /// @param contactEndCallback Lua function that will be called when this body ends collision
    /// @param data Any user data that might need to stored. For example: reference to object that owns the body
    PhysicsBody(PhysicsWorld *world, Vector2 position, ColliderShape const &shape, int32_t type, luabridge::LuaRef contactBeginCallback, luabridge::LuaRef contactEndCallback, luabridge::LuaRef data);

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
    void setIsActive(bool active);

    bool getIsActive() const { return m_active; }

    b2Body *getBody() { return m_body; }

    /// @brief Apply updated values to the body. This function assumes does nothing if it's called when world is locked
    void update();

    ~PhysicsBody();

    static void bindLua(lua_State *state);

private:
    PhysicsWorld *m_world;
    b2Body *m_body;
    luabridge::LuaRef m_contactBeginCallback;
    luabridge::LuaRef m_contactEndCallback;
    luabridge::LuaRef m_data;
    bool m_active = true;
};