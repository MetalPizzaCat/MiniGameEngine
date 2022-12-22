#include "CollisionCallback.hpp"

void CollisionCallback::BeginContact(b2Contact *contact)
{
    void *mainBodyData = contact->GetFixtureA()->GetBody()->GetUserData();
    void *otherBodyData = contact->GetFixtureB()->GetBody()->GetUserData();
    PhysicsBody *mainBody = nullptr;
    PhysicsBody *otherBody = nullptr;
    if (mainBodyData != nullptr)
    {
        mainBody = static_cast<PhysicsBody *>(mainBodyData);
    }
    if (otherBodyData != nullptr)
    {
        otherBody = static_cast<PhysicsBody *>(otherBodyData);
    }
    if (mainBodyData != nullptr)
    {
        mainBody->BeginContact(otherBody);
    }
    if (otherBodyData != nullptr)
    {
        otherBody->BeginContact(mainBody);
    }
}

void CollisionCallback::EndContact(b2Contact *contact)
{
    void *mainBodyData = contact->GetFixtureA()->GetBody()->GetUserData();
    void *otherBodyData = contact->GetFixtureB()->GetBody()->GetUserData();
    PhysicsBody *mainBody = nullptr;
    PhysicsBody *otherBody = nullptr;
    if (mainBodyData != nullptr)
    {
        mainBody = static_cast<PhysicsBody *>(mainBodyData);
    }
    if (otherBodyData != nullptr)
    {
        otherBody = static_cast<PhysicsBody *>(otherBodyData);
    }
    if (mainBodyData != nullptr)
    {
        mainBody->EndContact(otherBody);
    }
    if (otherBodyData != nullptr)
    {
        otherBody->EndContact(mainBody);
    }
}