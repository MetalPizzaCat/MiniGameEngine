#pragma once
#include <cstddef>
#include <SDL2/SDL.h>
#include "../Graphics/Vector.hpp"

enum class MouseButton : uint8_t
{
    Left = SDL_BUTTON_LEFT,
    Right = SDL_BUTTON_RIGHT,
    Middle = SDL_BUTTON_MIDDLE

};

enum class MouseEventType : uint8_t
{
    Press,
    Release,
    Motion
};

struct MouseState
{
    Vector2 position;
    uint8_t button;
    bool pressed;
    bool released;
    int32_t clicks;

    static void bindLua(lua_State *state);
};

struct MouseEvent
{
    MouseState state;
    uint8_t eventType;

    static void bindLua(lua_State *state);
};