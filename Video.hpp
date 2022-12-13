#pragma once
#include <cstddef>
#include <memory>
#include <string.h>
#include "Color.hpp"
#include "Vector.hpp"

using byte = unsigned char;

/// @brief Class for managing a video graphics array memory
class Video
{
public:
    static const size_t bytesPerPixel = 4;
    Video(size_t width, size_t height) : m_width(width), m_height(height)
    {
        m_vga = new byte[m_width * m_height * bytesPerPixel];
        memset(m_vga, 0, m_width * m_height * bytesPerPixel);
    }

    void drawPixel(Vector2 const &pos, Color const &color);

    void drawRect(Vector2 const &pos, Vector2 const &size, Color const &color);

    void clear();

    byte *getMemory() { return m_vga; }
    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }

    ~Video()
    {
        delete[] m_vga;
    }

private:
    size_t m_width;
    size_t m_height;
    byte *m_vga;
};

namespace LuaBind
{
    void bindVideo(lua_State *state);
}