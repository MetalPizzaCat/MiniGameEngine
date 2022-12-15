#include "Texture.hpp"
#include "../Log.hpp"
#include <fmt/core.h>

Texture::Texture(SDL_Renderer *renderer, const char *path) : m_path(path)
{
    SDL_Surface *file = IMG_Load(path);
    if (file == nullptr)
    {
        Log::error(fmt::format("Unable to load image: {}. Error: {}", path, IMG_GetError()));
        // TODO: replace with proper exit handling(like exception :) )
        exit(EXIT_FAILURE);
    }
    m_texture = SDL_CreateTextureFromSurface(renderer, file);
    SDL_FreeSurface(file);
}