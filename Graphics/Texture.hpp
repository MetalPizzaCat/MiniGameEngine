#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
public:
    Texture(SDL_Renderer *renderer, const char *path);

    SDL_Texture *getTexture() const { return m_texture; }
    std::string getPath() const { return m_path; }
    ~Texture()
    {
        SDL_DestroyTexture(m_texture);
    }

private:
    SDL_Texture *m_texture;
    std::string m_path;
};