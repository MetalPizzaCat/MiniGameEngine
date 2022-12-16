#include "Text.hpp"

void Text::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Text>("Text")
        .addProperty("text", &Text::getText, &Text::setText)
        .addProperty("color", &Text::getColor, &Text::setColor)
        .addProperty("position", &Text::m_position)
        .addProperty("scale", &Text::m_scale)
        .addFunction("draw", &Text::draw)
        .addConstructor<void (*)(Video *, std::string const &, Color, Vector2)>()
        .endClass();
}

void Text::setColor(Color color)
{
    m_color = color;
    setText(m_text);
}

void Text::setText(std::string const &text)
{
    m_text = text;
    SDL_Surface *textSurf = TTF_RenderText_Solid(m_video->getDefaultFont(), text.c_str(), SDL_Color{.r = m_color.r, .g = m_color.g, .b = m_color.b, .a = SDL_ALPHA_OPAQUE});
    if (textSurf == nullptr)
    {
        Log::error(fmt::format("Unable to create text texture: {}", TTF_GetError()));
        return;
    }
    m_texture = SDL_CreateTextureFromSurface(m_video->getRenderer(), textSurf);
    if (m_texture == nullptr)
    {
        Log::error(fmt::format("Unable to create text texture: {}", SDL_GetError()));
        return;
    }
    m_textWidth = textSurf->w;
    m_textHeight = textSurf->h;

    SDL_FreeSurface(textSurf);
}

void Text::draw()
{
    m_video->drawTextureRaw(m_position, Vector2((float)m_textWidth * m_scale.x, (float)m_textHeight * m_scale.y), m_texture);
}