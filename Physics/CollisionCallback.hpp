#pragma once
#include "PhysicsBody.hpp"

/// @brief Class for handling contacts between objects
class CollisionCallback : b2ContactListener
{
public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};