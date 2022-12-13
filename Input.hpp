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

private:
    std::map<int32_t, bool> m_physicalKeys;
    std::map<int32_t, bool> m_virtualKeys;

    std::map<std::string, int32_t> m_inputs;
};

namespace LuaBind
{
    void bindInput(lua_State *state)
    {
        luabridge::getGlobalNamespace(state)
            .beginClass<Input>("Input")
            .addFunction("is_key_pressed", &Input::isKeyPressed)
            .addFunction("is_physical_key_pressed", &Input::isPhysicalKeyPressed)
            .addFunction("is_input_pressed", &Input::isInputPressed)
            .endClass();
    }

    void bindKeys(lua_State *state)
    {
        luabridge::push(state, (int32_t)SDL_SCANCODE_UP);
        lua_setglobal(state, "KEY_PHYS_UP");
        luabridge::push(state, (int32_t)SDL_SCANCODE_DOWN);
        lua_setglobal(state, "KEY_PHYS_DOWN");
        luabridge::push(state, (int32_t)SDL_SCANCODE_LEFT);
        lua_setglobal(state, "KEY_PHYS_LEFT");
        luabridge::push(state, (int32_t)SDL_SCANCODE_RIGHT);
        lua_setglobal(state, "KEY_PHYS_RIGHT");
    }
}