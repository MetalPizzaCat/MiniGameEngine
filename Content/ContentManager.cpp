#include "ContentManager.hpp"

void ContentManager::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<ContentManager>("ContentManager")
        .addFunction("load_texture", &ContentManager::loadTexture)
        .endClass();
}

TextureResource *ContentManager::loadTexture(std::string path)
{
    std::map<size_t, Resource<Texture> *>::iterator it = std::find_if(
        m_textures.begin(),
        m_textures.end(),
        [path](std::pair<size_t, Resource<Texture> *> const &tex)
        { return tex.second->resource->getPath() == path; });
    if (it != m_textures.end())
    {
        return new TextureResource(path, (*it).first, this);
    }

    Texture *texture = new Texture(m_renderer, path.c_str());
    m_textures.try_emplace(
        m_textureId, new Resource<Texture>{.resource = texture, .refCount = 1});
    return new TextureResource(path, m_textureId++, this);
}

Texture *ContentManager::getTexture(size_t id)
{
    std::map<size_t, Resource<Texture> *>::iterator it = m_textures.find(id);
    return it == m_textures.end() ? nullptr : (*it).second->resource;
}

void ContentManager::freeTexture(size_t id)
{
    m_textures[id]->refCount--;
    if (m_textures[id]->refCount <= 0)
    {
        delete m_textures[id]->resource;
        m_textures.erase(id);
    }
}