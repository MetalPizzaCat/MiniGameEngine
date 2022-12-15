#include "TextureResource.hpp"
#include "ContentManager.hpp"

TextureResource::~TextureResource()
{
    m_manager->freeTexture(m_id);
}

Texture *TextureResource::getTexture()
{
    m_manager->getTexture(m_id);
}

void TextureResource::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<TextureResource>("Texture")
        .addProperty("id", &TextureResource::m_id, false)
        .endClass();
}