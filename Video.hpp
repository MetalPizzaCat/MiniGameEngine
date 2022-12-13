#pragma once
#include <cstddef>
#include <memory>
#include <string.h>
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "Vector.hpp"

using byte = unsigned char;

/// @brief Class for managing a video graphics array memory
class Video
{
public:
    static const size_t bytesPerPixel = 4;
    Video(size_t width, size_t height, SDL_Renderer *renderer) : m_width(width), m_height(height), m_renderer(renderer)
    {
        m_vgaTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_TARGET, width, height);
        SDL_SetRenderTarget(renderer, m_vgaTexture);
    }
    void draw(size_t screenWidth, size_t screenHeight);

    void drawPixel(Vector2 const &pos, Color const &color);

    void drawRect(Vector2 const &pos, Vector2 const &size, Color const &color);

    void drawCircle(Vector2 const &pos, size_t radius, Color const &color);

    void clear();

    SDL_Renderer *getRenderer() { return m_renderer; }
    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }

    ~Video()
    {
        SDL_DestroyRenderer(m_renderer);
    }

private:
    size_t m_width;
    size_t m_height;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_vgaTexture;
};

namespace LuaBind
{
    void bindVideo(lua_State *state);
}