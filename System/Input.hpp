#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
#include <SDL2/SDL.h>

#include <map>
#include <algorithm>

#include "../Graphics/Vector.hpp"
#include "Mouse.hpp"


/// @brief Class that handles info related to input state
class Input
{
public:
    Input() = default;
    /// @brief Is current virtual SDL key pressed
    /// @param keyId SDL_keycode virtual key id
    /// @return True if pressed
    bool isKeyPressed(int32_t keyId)
    {
        // if count returns 0 means no key with this id was registered yet
        return m_virtualKeys.count(keyId) ? m_virtualKeys[keyId] : false;
    }
    /// @brief Is current physical key pressed
    /// @param keyId SDl_Scancode key id
    /// @return True if pressed
    bool isPhysicalKeyPressed(int32_t keyId)
    {
        // if count returns 0 means no key with this id was registered yet
        return m_physicalKeys.count(keyId) ? m_physicalKeys[keyId] : false;
    }
    /// @brief Is named input pressed
    /// @param input Name of the input
    /// @return True if pressed
    bool isInputPressed(const char *input)
    {
        // TODO: add input system
        return false;
    }

    bool isMouseButtonPressed(uint8_t btn)
    {
        return m_mouse.count((MouseButton)btn) ? m_mouse[(MouseButton)btn].pressed : false;
    }

    void setInputState(SDL_Keysym key, bool state);

    void setMouseButtonState(MouseButton btn, MouseState const &state)
    {
        m_mouse[btn] = state;
    }

    static void bindInput(lua_State *state);

private:
    std::map<int32_t, bool> m_physicalKeys;
    std::map<int32_t, bool> m_virtualKeys;

    std::map<std::string, int32_t> m_inputs;

    std::map<MouseButton, MouseState> m_mouse;
};

namespace LuaBind
{
    void bindKeys(lua_State *state);
}