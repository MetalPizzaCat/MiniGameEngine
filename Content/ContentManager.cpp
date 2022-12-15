#include "ContentManager.hpp"

void ContentManager::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<ContentManager>("ContentManager")
        .addFunction("load_texture", &ContentManager::loadTexture)
        .endClass();
}