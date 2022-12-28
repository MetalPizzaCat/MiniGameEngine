#include "Input.hpp"

void Input::bindInput(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Input>("Input")
        .addFunction("is_key_pressed", &Input::isKeyPressed)
        .addFunction("is_physical_key_pressed", &Input::isPhysicalKeyPressed)
        .addFunction("is_input_pressed", &Input::isInputPressed)
        .addFunction("is_mouse_button_pressed", &Input::isMouseButtonPressed)
        .endClass();
}

void Input::setInputState(SDL_Keysym key, bool state)
{
    m_physicalKeys[key.scancode] = state;
    m_virtualKeys[key.sym] = state;
}


void LuaBind::bindKeys(lua_State *state)
{
    luabridge::push(state, (int32_t)SDL_SCANCODE_UP);
    lua_setglobal(state, "KEY_PHYS_UP");
    luabridge::push(state, (int32_t)SDL_SCANCODE_DOWN);
    lua_setglobal(state, "KEY_PHYS_DOWN");
    luabridge::push(state, (int32_t)SDL_SCANCODE_LEFT);
    lua_setglobal(state, "KEY_PHYS_LEFT");
    luabridge::push(state, (int32_t)SDL_SCANCODE_RIGHT);
    lua_setglobal(state, "KEY_PHYS_RIGHT");
    luabridge::push(state, (int32_t)MouseButton::Left);
    lua_setglobal(state, "MOUSE_BUTTON_LEFT");
    luabridge::push(state, (int32_t)MouseButton::Right);
    lua_setglobal(state, "MOUSE_BUTTON_RIGHT");
    luabridge::push(state, (int32_t)MouseButton::Middle);
    lua_setglobal(state, "MOUSE_BUTTON_MIDDLE");
}