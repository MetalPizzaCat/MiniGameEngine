#include "Mouse.hpp"

void MouseState::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<MouseState>("MouseState")
        .addProperty("is_pressed", &MouseState::pressed)
        .addProperty("is_released", &MouseState::released)
        .addProperty("position", &MouseState::position)
        .addProperty("click_count", &MouseState::clicks)
        .addProperty("button", &MouseState::button)
        .endClass();
}

void MouseEvent::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<MouseEvent>("MouseEvent")
        .addProperty("mouse", &MouseEvent::state)
        .addProperty("type", &MouseEvent::eventType)
        .endClass();

    luabridge::push(state, (int32_t)MouseEventType::Motion);
    lua_setglobal(state, "MOUSE_EVENT_MOTION");
    luabridge::push(state, (int32_t)MouseEventType::Press);
    lua_setglobal(state, "MOUSE_EVENT_PRESS");
    luabridge::push(state, (int32_t)MouseEventType::Release);
    lua_setglobal(state, "MOUSE_EVENT_RELEASE");
}