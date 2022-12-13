#include "Video.hpp"

void LuaBind::bindVideo(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Video>("Video")
        .addFunction("draw_point", &Video::drawPixel)
        .addFunction("draw_rect", &Video::drawRect)
        .addFunction("clear", &Video::clear)
        //.addProperty("ScreenWidth", &Video::getWidth, false)
        //.addProperty("ScreenHeight", &Video::getHeight, false)
        .endClass();
}

void Video::drawPixel(Vector2 const &pos, Color const &color)
{
    if (pos.x < 0 || pos.y < 0)
    {
        return;
    }
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 0] = 0; // fun fact: you can write anything here :D
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 1] = color.b;
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 2] = color.g;
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 3] = color.r;
}

void Video::drawRect(Vector2 const &pos, Vector2 const &size, Color const &color)
{
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 0] = 0; // fun fact: you can write anything here :D
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 1] = color.b;
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 2] = color.g;
    m_vga[(size_t)pos.x * bytesPerPixel + (size_t)pos.y * bytesPerPixel * m_width + 3] = color.r;
}

void Video::clear()
{
    memset(m_vga, 0, m_width * m_height * bytesPerPixel);
}