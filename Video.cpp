#include "Video.hpp"
#include <algorithm>
#include <SDL2/SDL2_gfxPrimitives.h>

void LuaBind::bindVideo(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Video>("Video")
        .addFunction("draw_point", &Video::drawPixel)
        .addFunction("draw_rect", &Video::drawRect)
        .addFunction("draw_circle", &Video::drawCircle)
        .addFunction("clear", &Video::clear)
        //.addProperty("ScreenWidth", &Video::getWidth, false)
        //.addProperty("ScreenHeight", &Video::getHeight, false)
        .endClass();
}

void Video::draw(size_t screenWidth, size_t screenHeight)
{
    SDL_RenderPresent(m_renderer);
    // set target to be window
    SDL_SetRenderTarget(m_renderer, nullptr);
    SDL_Rect vgaRect{.x = 0, .y = 0, .w = screenWidth - 100, .h = screenHeight - 100};
    SDL_RenderCopy(m_renderer, m_vgaTexture, nullptr, &vgaRect);
    SDL_RenderDrawPointF(m_renderer, 5.f, 50.f);
    SDL_RenderPresent(m_renderer);
    // set to texture mode
    SDL_SetRenderTarget(m_renderer, m_vgaTexture);
}

void Video::drawCircle(Vector2 const &pos, size_t radius, Color const &color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    filledCircleRGBA(m_renderer, (int32_t)pos.x, (int32_t)pos.y, radius, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
}

void Video::drawPixel(Vector2 const &pos, Color const &color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPointF(m_renderer, pos.x, pos.y);
}

void Video::drawRect(Vector2 const &pos, Vector2 const &size, Color const &color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_FRect rect{.x = pos.x, .y = pos.y, .w = size.x, .h = size.y};
    SDL_RenderFillRectF(m_renderer, &rect);
}

void Video::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}