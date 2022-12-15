#pragma once
#include <cstddef>
#include <memory>
#include <string.h>
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "Vector.hpp"
#include "../Content/TextureResource.hpp"

using byte = unsigned char;

/// @brief Class that handles all of the graphics interactions
class Video
{
public:
    Video(size_t width, size_t height, SDL_Renderer *renderer) : m_width(width), m_height(height), m_renderer(renderer)
    {
        m_vgaTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_TARGET, width, height);
        SDL_SetRenderTarget(renderer, m_vgaTexture);
    }

    /// @brief Draw contents of the buffer to the screen
    /// @param screenWidth
    /// @param screenHeight
    void draw(size_t screenWidth, size_t screenHeight);

    /// @brief Plot single pixel on the canvas
    /// @param pos Location
    /// @param color
    void drawPixel(Vector2 const &pos, Color const &color);

    /// @brief Draws a filled rectangle
    /// @param pos Location
    /// @param size Size of the rectangle
    /// @param color Color
    void drawRect(Vector2 const &pos, Vector2 const &size, Color const &color);

    /// @brief Draw a filled circle
    /// @param pos Location
    /// @param radius Radius of the circle
    /// @param color Color
    void drawCircle(Vector2 const &pos, size_t radius, Color const &color);

    /// @brief Draws a line from point A to point B
    /// @param a Start location
    /// @param b End location
    /// @param color Color
    void drawLine(Vector2 const &a, Vector2 const &b, Color const &color);

    /// @brief Draws texture at given coords
    /// @param pos Location
    void drawTexture(Vector2 const &pos, Vector2 const &size, TextureResource *tex);

    /// @brief Clears the screen with black color
    void clear();

    /// @brief Bind Video class to lua state to make it accessible
    /// @param state
    static void bindLua(lua_State *state);

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
