#include "PhysicsDebug.hpp"
#include <vector>
#include "../Graphics/Vector.hpp"

void PhysicsDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    std::vector<Vector2> points;
    for (int32_t i = 0; i < vertexCount; i++)
    {
        points.emplace_back(vertices[i].x, vertices[i].y);
    }
    m_graphics->drawPolygon(points, Color(color.r, color.g, color.b));
}
void PhysicsDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    std::vector<Vector2> points;
    for (int32_t i = 0; i < vertexCount; i++)
    {
        points.emplace_back(vertices[i].x, vertices[i].y);
    }
    m_graphics->drawPolygon(points, Color(color.r, color.g, color.b));
}
void PhysicsDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)
{
    m_graphics->drawCircle(Vector2(center.x - radius / 2.f, center.y - radius / 2.f), (int32_t)radius, Color(color.r, color.g, color.b));
}
void PhysicsDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
{
    m_graphics->drawCircle(Vector2(center.x - radius / 2.f, center.y - radius / 2.f), (int32_t)radius, Color(color.r, color.g, color.b));
}
void PhysicsDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
    m_graphics->drawLine(Vector2(p1.x, p1.y), Vector2(p2.x, p2.y), Color(color.r, color.g, color.b));
}
void PhysicsDebugDraw::DrawTransform(const b2Transform &xf)
{
}