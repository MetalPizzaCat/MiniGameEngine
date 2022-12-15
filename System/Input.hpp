#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
#include <SDL2/SDL.h>

#include <map>
#include <algorithm>

class Input
{
public:
    Input() = default;
    bool isKeyPressed(int32_t keyId)
    {
        // if count returns 0 means no key with this id was registered yet
        return m_virtualKeys.count(keyId) ? m_virtualKeys[keyId] : false;
    }
    bool isPhysicalKeyPressed(int32_t keyId)
    {
        // if count returns 0 means no key with this id was registered yet
        return m_physicalKeys.count(keyId) ? m_physicalKeys[keyId] : false;
    }
    bool isInputPressed(const char *input)
    {
        return false;
    }

    void setInputState(SDL_Keysym key, bool state)
    {
        m_physicalKeys[key.scancode] = state;
        m_virtualKeys[key.sym] = state;
    }

    static void bindInput(lua_State *state);

private:
    std::map<int32_t, bool> m_physicalKeys;
    std::map<int32_t, bool> m_virtualKeys;

    std::map<std::string, int32_t> m_inputs;
};

namespace LuaBind
{
    void bindKeys(lua_State *state);
}