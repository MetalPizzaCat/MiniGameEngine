#include "Input.hpp"

void Input::bindInput(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Input>("Input")
        .addFunction("is_key_pressed", &Input::isKeyPressed)
        .addFunction("is_physical_key_pressed", &Input::isPhysicalKeyPressed)
        .addFunction("is_input_pressed", &Input::isInputPressed)
        .endClass();
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
}