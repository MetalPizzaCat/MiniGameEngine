#pragma once
#include <vector>
#include <string>
#include <array>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <LuaBridge/LuaBridge.h>

#include "Log.hpp"

struct SystemState
{
    size_t mouseX;
    size_t mouseY;

    size_t graphicsWidth;
    size_t graphicsHeight;

    int32_t lastPressedKey;
};

/// @brief Class that stores information that can be accessed from lua code
class System
{
public:
    System() = default;
    void print(const char *text)
    {
        m_output.emplace_back(text);
        Log::error(text);
    }

    static void bindLua(lua_State *state);

private:
    /// @brief Current screen output
    std::vector<std::string> m_output;
};
