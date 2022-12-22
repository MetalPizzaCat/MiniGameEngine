#pragma once
#include <Box2D/Box2D.h>
#include "../Lua/LuaMachine.hpp"

/// @brief Base class for all collision shapes
class ColliderShape
{
public:
    /// @brief Get box2d fixture object
    /// @return box2d fixture object
    const b2FixtureDef *getFixtureDef() const { return &m_def; }

    virtual ~ColliderShape() = default;

    static void bindLua(lua_State *state);

protected:
    b2FixtureDef m_def;
};

class CircleColliderShape : public ColliderShape
{
public:
    CircleColliderShape(float radius) : m_radius(radius)
    {
        m_circle.m_radius = radius / PHYSICS_SCALE;
        m_circle.m_p = b2Vec2(m_radius / PHYSICS_SCALE, m_radius / PHYSICS_SCALE);
        m_def.shape = &m_circle;
    }
    static void bindLua(lua_State *state);

private:
    float m_radius;
    b2CircleShape m_circle;
};

class RectangleColliderShape : public ColliderShape
{

public:
    RectangleColliderShape(float width, float height)
    {
        m_rect.SetAsBox((width / 2.f) / PHYSICS_SCALE, (height / 2.f) / PHYSICS_SCALE);
        m_def.shape = &m_rect;
    }

    static void bindLua(lua_State *state);

private:
    b2PolygonShape m_rect;
};
