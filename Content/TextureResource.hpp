#pragma once

#include <string>
#include "../Graphics/Texture.hpp"
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>

class ContentManager;
class TextureResource
{
public:
    TextureResource(std::string str, size_t id, ContentManager *manager) : m_id(id), m_manager(manager)
    {
    }
    Texture *getTexture();

    static void bindLua(lua_State *state);

    ~TextureResource();

private:
    /// @brief Content manager that holds the actual textures
    ContentManager *m_manager;

    size_t m_id;
    size_t m_width;
    size_t m_height;
};