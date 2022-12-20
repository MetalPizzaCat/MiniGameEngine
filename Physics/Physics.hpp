#pragma once

#include "PhysicsWorld.hpp"
#include "PhysicsBody.hpp"
#include "ColliderShape.hpp"
#include "../Lua/LuaMachine.hpp"

void bindPhysicsToLua(lua_State *state);