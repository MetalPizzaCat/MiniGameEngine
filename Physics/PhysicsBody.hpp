#pragma once
// #include "PhysicsWorld.hpp"
#include "ColliderShape.hpp"
#include "../Graphics/Vector.hpp"
#include "../Lua/LuaMachine.hpp"

class PhysicsWorld;

/// @brief Struct that contains data needed to create a body
struct PhysicsBodyDefintion
{
    /// @brief Static, kinematic or dynamic
    uint8_t bodyType;
    /// @brief  Struct containing collision shape info
    ColliderShape shape;
    /// @brief If true body will respond to collisions but not interact with physics bodies
    bool isSensor;
    /// @brief Collision category bits. Which collision group does this body belong to
    uint16_t bodyCategory;
    /// @brief  Collision mask bits. Which collision groups does this body collide with
    uint16_t collisionMask;

    /// @brief Creates a new body definition info struct
    /// @param bodyType Static, kinematic or dynamic. See PhysicsBody::Type
    /// @param shape Struct containing collision shape info
    /// @param isSensor If true body will respond to collisions but not interact with physics bodies
    /// @param bodyCategory Collision category bits. Which collision group does this body belong to
    /// @param collisionMask Collision mask bits. Which collision groups does this body collide with
    PhysicsBodyDefintion(uint8_t bodyType, ColliderShape const &shape, bool isSensor, uint16_t bodyCategory, uint16_t collisionMask) : bodyType(bodyType), shape(shape), isSensor(isSensor), bodyCategory(bodyCategory), collisionMask(collisionMask) {}

    static void bindLua(lua_State *state);
};

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
    /// @param world Pointer to the physics world that manages all of the bodies
    /// @param position Position to spawn body at
    /// @param bodyDef Struct with info needed to create a body
    /// @param contactBeginCallback Lua function that will be called when this body collides
    /// @param contactEndCallback Lua function that will be called when this body ends collision
    /// @param data Any user data that might need to stored. For example: reference to object that owns the body
    PhysicsBody(PhysicsWorld *world, Vector2 position, PhysicsBodyDefintion const &bodyDef, luabridge::LuaRef contactBeginCallback, luabridge::LuaRef contactEndCallback, luabridge::LuaRef data);

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