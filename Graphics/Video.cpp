#include "Video.hpp"
#include <algorithm>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <fmt/core.h>
#include "../Log.hpp"

void Video::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .beginClass<Video>("Video")
        .addFunction("draw_point", &Video::drawPixel)
        .addFunction("draw_rect", &Video::drawRect)
        .addFunction("draw_circle", &Video::drawCircle)
        .addFunction("draw_line", &Video::drawLine)
        .addFunction("draw_texture", &Video::drawTexture)
        .addFunction("draw_text", &Video::drawText)
        .addFunction("clear", &Video::clear)
        .addProperty("screen_width", &Video::m_width, false)
        .addProperty("screen_height", &Video::m_height, false)
        .endClass();
}

void Video::draw(size_t screenWidth, size_t screenHeight)
{
    SDL_RenderPresent(m_renderer);
    // set target to be window
    SDL_SetRenderTarget(m_renderer, nullptr);
    SDL_Rect vgaRect{.x = 0, .y = 0, .w = screenWidth, .h = screenHeight};
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

void Video::drawLine(Vector2 const &a, Vector2 const &b, Color const &color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLineF(m_renderer, a.x, a.y, b.x, b.y);
}

void Video::drawTexture(Vector2 const &pos, Vector2 const &size, TextureResource *tex)
{
    SDL_FRect rect{.x = pos.x, .y = pos.y, .w = size.x, .h = size.y};
    SDL_Rect srcRect{.x = 0, .y = 0, .w = 32, .h = 32};
    if (tex == nullptr || tex->getTexture() == nullptr || tex->getTexture()->getTexture() == nullptr)
    {
        Log::error("Attempted to draw null texture");
        return;
    }
    if (SDL_RenderCopyF(m_renderer, tex->getTexture()->getTexture(), nullptr, &rect) == -1)
    {
        Log::error(fmt::format("Failed to render texture : {}", SDL_GetError()));
    }
}

void Video::drawTextureRaw(Vector2 const &pos, Vector2 const &size, SDL_Texture *texture)
{
    SDL_FRect rect{.x = pos.x, .y = pos.y, .w = size.x, .h = size.y};
    if (texture == nullptr)
    {
        Log::error("Attempted to draw null texture");
        return;
    }
    if (SDL_RenderCopyF(m_renderer, texture, nullptr, &rect) == -1)
    {
        Log::error(fmt::format("Failed to render texture : {}", SDL_GetError()));
    }
}

void Video::drawText(Vector2 const &pos, std::string const &text, Color const &color)
{
    SDL_Surface *textSurf = TTF_RenderText_Solid(m_defaultFont, text.c_str(), SDL_Color{.r = color.r, .g = color.g, .b = color.b, .a = SDL_ALPHA_OPAQUE});
    if (textSurf == nullptr)
    {
        Log::error(fmt::format("Unable to create text texture: {}", TTF_GetError()));
        return;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(m_renderer, textSurf);
    if (tex == nullptr)
    {
        Log::error(fmt::format("Unable to create text texture: {}", SDL_GetError()));
        return;
    }

    SDL_FRect rect{.x = pos.x, .y = pos.y, .w = textSurf->w, .h = textSurf->h};
    if (SDL_RenderCopyF(m_renderer, tex, nullptr, &rect) == -1)
    {
        Log::error(fmt::format("Failed to render text : {}", SDL_GetError()));
        return;
    }
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(tex);
}

void Video::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}