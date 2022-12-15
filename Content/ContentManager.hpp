#pragma once
#include "../Graphics/Texture.hpp"
#include "TextureResource.hpp"
#include <map>
#include <algorithm>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
#include "../Log.hpp"

template <typename T>
struct Resource
{
    T *resource;
    size_t refCount;
};

class ContentManager
{
public:
    TextureResource *loadTexture(std::string path);

    Texture *getTexture(size_t id);

    void freeTexture(size_t id);

    void setRenderer(SDL_Renderer *renderer)
    {
        m_renderer = renderer;
    }

    static void bindLua(lua_State *state);

    ~ContentManager()
    {
        Log::info("Content manager freed");
    }

private:
    std::map<size_t, Resource<Texture>*> m_textures;
    SDL_Renderer *m_renderer;
    size_t m_textureId = 0;
};