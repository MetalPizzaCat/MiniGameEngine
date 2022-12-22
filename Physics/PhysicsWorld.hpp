#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include "../Graphics/Vector.hpp"
#include "../Lua/LuaMachine.hpp"
#include "PhysicsBody.hpp"

class PhysicsWorldException : public std::exception
{
public:
    /// @brief Create an exception
    /// @param message Message as c string
    explicit PhysicsWorldException(const char *message)
        : m_msg(message) {}

    /// @brief Create an exception
    /// @param message Message as c++ string
    explicit PhysicsWorldException(const std::string &message)
        : m_msg(message) {}

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~PhysicsWorldException() noexcept {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
    virtual const char *what() const noexcept
    {
        return m_msg.c_str();
    }

protected:
    std::string m_msg;
};

namespace PhysicsHelpers
{
    b2Vec2 fromVector2(Vector2 const &vec);
}

/// @brief Wrapper around Box2D world. Simulates physics itself and manages all of the object in the physics world
class PhysicsWorld
{
public:
    PhysicsWorld(Vector2 gravity, b2ContactListener *contactListener)
    {
        m_world = std::make_unique<b2World>(PhysicsHelpers::fromVector2(gravity));
        m_world->SetContactListener(contactListener);
    }

    /// @brief Call physics update fuctions
    /// @param timeStep physics update delta
    void step(float32 timeStep);

    /// @brief Get Box2D world object
    /// @return Box2D world object
    b2World *getWorld() { return m_world.get(); }

    void setGravity(Vector2 const &gravity);

    Vector2 getGravity() const;

    /// @brief Returns scale world to pixel scale, value is same as PHYSICS_SCALE macro defined in project
    /// @return
    float getWorldScale() const { return m_worldScale; }

    void setDebugDraw(b2Draw *debug);

    static void bindLua(lua_State *state);

    /// @brief Safely destroys body object. Because box2d manages all bodies,
    /// instead of freeing memory manually using  delete or free(), memory allocated for the body will be freed by the world
    /// @param body Body to destroy
    void destroyBody(PhysicsBody *body);

    /// @brief Creates a new body using PhysicsBody constructor and registers it into the world for update notification
    /// @param position Where will the body be spawned
    /// @param shape Shape of the body
    /// @param type Type of the body. See PhysicsBody::Type enum
    /// @param contactBeginCallback Lua function that will be called when this body collides
    /// @param contactEndCallback Lua function that will be called when this body ends collision
    /// @param data Any user data that might need to stored. For example: reference to object that owns the body
    PhysicsBody *createBody(Vector2 position, ColliderShape const &shape, int32_t type, luabridge::LuaRef contactBeginCallback, luabridge::LuaRef contactEndCallback, luabridge::LuaRef data);

private:
    /// @brief Performs destruction of all bodies marked as "dead"
    void freeBodies();
    /// @brief Collection of bodies that should be deleted at the end of the frame
    std::vector<b2Body *> m_deadBodies;

    std::vector<PhysicsBody *> m_bodies;

    std::unique_ptr<b2World> m_world;
    int32_t m_velocityIterCount = 6;
    int32_t m_positionIterCount = 2;
    float m_worldScale = PHYSICS_SCALE;
};