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
    TextureResource *loadTexture(std::string path)
    {
        std::map<size_t, Resource<Texture>*>::iterator it = std::find_if(
            m_textures.begin(),
            m_textures.end(),
            [path](std::pair<size_t, Resource<Texture>*> const &tex)
            { return tex.second->resource->getPath() == path; });
        if (it != m_textures.end())
        {
            return new TextureResource(path, (*it).first,  this);
        }

        Texture *texture = new Texture(m_renderer, path.c_str());
        m_textures.try_emplace(
            m_textureId, new Resource<Texture>{.resource = texture, .refCount = 1});
        return new TextureResource(path, m_textureId++, this);
    }

    Resource<Texture> *getTexture(size_t id)
    {
        std::map<size_t, Resource<Texture>*>::iterator it = m_textures.find(id);
        return it == m_textures.end() ? nullptr : (*it).second;
    }

    void freeTexture(size_t id)
    {
        m_textures[id]->refCount--;
        if (m_textures[id]->refCount <= 0)
        {
            delete m_textures[id]->resource;
            m_textures.erase(id);
        }
    }

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