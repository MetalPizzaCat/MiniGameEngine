#pragma once
#include <Box2D/Box2D.h>
#include <memory>
#include "../Graphics/Vector.hpp"

namespace PhysicsHelpers
{
    b2Vec2 fromVector2(Vector2 const &vec);
}

class PhysicsWorld
{
public:
    PhysicsWorld(Vector2 gravity)
    {
        m_world = std::make_unique<b2World>(PhysicsHelpers::fromVector2(gravity));
    }

    void step(float32 timeStep);
    b2World *getWorld() { return m_world.get(); }
    float getWorldScale() const { return m_worldScale; }

    void setDebugDraw(b2Draw *debug);

    static void bindLua(lua_State *state);

private:
    std::unique_ptr<b2World> m_world;
    int32_t m_velocityIterCount = 6;
    int32_t m_positionIterCount = 2;
    float m_worldScale = PHYSICS_SCALE;
};