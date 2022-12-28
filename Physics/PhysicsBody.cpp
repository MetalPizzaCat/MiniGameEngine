#include "PhysicsBody.hpp"
#include "PhysicsWorld.hpp"

void PhysicsBodyDefintion::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsBodyDefintion>("BodyDef")
        .addProperty("body_type", &PhysicsBodyDefintion::bodyType)
        .addProperty("shape", &PhysicsBodyDefintion::shape)
        .addProperty("is_sensor", &PhysicsBodyDefintion::isSensor)
        .addProperty("collision_category", &PhysicsBodyDefintion::bodyCategory)
        .addProperty("collision_mask", &PhysicsBodyDefintion::collisionMask)
        .addConstructor<void (*)(uint8_t, ColliderShape const &, bool, uint16_t, uint16_t)>()
        .endClass()
        .endNamespace();
}

void PhysicsBody::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginNamespace("Physics")
        .beginClass<PhysicsBody>("Body")
        .addFunction("get_position", &PhysicsBody::getPosition)
        .addFunction("get_rotation", &PhysicsBody::getRotation)
        .addProperty("velocity", &PhysicsBody::getVelocity, &PhysicsBody::setVelocity)
        .addProperty("on_collision_begin", &PhysicsBody::m_contactBeginCallback)
        .addProperty("on_collision_end", &PhysicsBody::m_contactEndCallback)
        .addProperty("data", &PhysicsBody::m_data)
        .addProperty("active", &PhysicsBody::getIsActive, &PhysicsBody::setIsActive)
        .endClass()
        .endNamespace();
}

PhysicsBody::PhysicsBody(PhysicsWorld *world, Vector2 position, PhysicsBodyDefintion const &bodyDefInfo, luabridge::LuaRef contactBeginCallback, luabridge::LuaRef contactEndCallback, luabridge::LuaRef data) : m_world(world),
                                                                                                                                                                                                                 m_contactBeginCallback(contactBeginCallback), m_contactEndCallback(contactEndCallback), m_data(data)
{
    b2BodyDef bodyDef;
    bodyDef.enabled = true;
    bodyDef.type = (b2BodyType)bodyDefInfo.bodyType;
    bodyDef.position.Set(position.x / PHYSICS_SCALE, position.y / PHYSICS_SCALE);
    m_body = m_world->getWorld()->CreateBody(&bodyDef);

    b2FixtureDef fixture = *bodyDefInfo.shape.getFixtureDef();
    fixture.filter.categoryBits = bodyDefInfo.bodyCategory;
    fixture.filter.maskBits = bodyDefInfo.collisionMask;

    m_body->CreateFixture(&fixture);
    m_body->GetUserData().pointer = (uintptr_t)this;
}

PhysicsBody::~PhysicsBody()
{
    m_world->destroyBody(this);
}

void PhysicsBody::setIsActive(bool active)
{
    m_active = active;
}

Vector2 PhysicsBody::getPosition() const
{
    return Vector2(m_body->GetPosition().x * m_world->getWorldScale(), m_body->GetPosition().y * m_world->getWorldScale());
}

float PhysicsBody::getRotation() const
{
    return m_body->GetAngle();
}

Vector2 PhysicsBody::getVelocity() const
{
    return Vector2(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
}

void PhysicsBody::setVelocity(Vector2 const &velocity)
{
    m_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void PhysicsBody::update()
{
    if (m_body->IsEnabled() != m_active)
    {
        m_body->SetEnabled(m_active);
    }
}

void PhysicsBody::BeginContact(PhysicsBody *other)
{
    if (!m_contactBeginCallback.isNil())
    {
        m_contactBeginCallback(this, other);
    }
}

void PhysicsBody::EndContact(PhysicsBody *other)
{
    if (!m_contactEndCallback.isNil())
    {
        m_contactEndCallback(this, other);
    }
}