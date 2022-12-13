#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <memory>
#include <chrono>
#include "LuaMachine.hpp"
#include "Log.hpp"
#include "Video.hpp"
#include "System.hpp"
#include "Input.hpp"

/// @brief Class that handles SDL window and communication between parts of software
class Window
{
public:
    static const size_t canvasWidth = 256;
    static const size_t canvasHeight = 256;
    Window(int32_t width, int32_t height) : m_width(width),
                                            m_height(height),
                                            m_running(true),
                                            m_video(new Video(canvasWidth, canvasHeight))
    {
        m_window = SDL_CreateWindow("Nema-Video v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

        if (!m_window || !m_renderer)
        {
            Log::error("Failed to init window and renderer");
            exit(EXIT_FAILURE);
        };
        m_lua = std::make_unique<LuaMachine>();
        bindLuaObjects();

        m_vgaTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, canvasWidth, canvasHeight);
    }

    /// @brief Loads given code into lua machine and executes _init function if present
    /// @param code Code that will be executed
    bool loadCode(const char *code)
    {
        return m_lua->loadCode(code) && m_lua->call("_init");
    }

    /// @brief Starts the game loop
    void run(const char *code)
    {
        if (!loadCode(code))
        {
            return;
        }
        while (m_running)
        {
            handleEvents();
            updateLua();
            clearScreen();
            render();
        }
    }

    LuaMachine *getLua() { return m_lua.get(); }

    ~Window()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_DestroyTexture(m_vgaTexture);
        delete m_video;
    }

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int32_t m_width;
    int32_t m_height;
    bool m_running;
    std::unique_ptr<LuaMachine> m_lua;
    Video *m_video;
    System m_system;
    Input m_input;

    SDL_Texture *m_vgaTexture;
    /// @brief Last time when clock was updated
    std::chrono::high_resolution_clock m_tick;

    void clearScreen()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
    }

    void render()
    {
        SDL_Rect rect{.x = 50, .y = 50, .w = 100, .h = 100};
        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(m_renderer, &rect);
        byte *texture = nullptr;
        int pitch;

        SDL_LockTexture(m_vgaTexture, nullptr, (void **)&texture, &pitch);
        memcpy(texture, m_video->getMemory(), m_video->getWidth() * Video::bytesPerPixel * m_video->getHeight());
        SDL_UnlockTexture(m_vgaTexture);
        SDL_Rect vgaRect{.x = 0, .y = 0, .w = m_width - 100, .h = m_height - 100};
        SDL_RenderCopy(m_renderer, m_vgaTexture, nullptr, &vgaRect);
        SDL_RenderPresent(m_renderer);
    }

    void updateLua()
    {
        m_lua->call("_update");
    }

    void handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                m_running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                m_input.setInputState(event.key.keysym, true);
            }
            else if (event.type == SDL_KEYUP)
            {
                m_input.setInputState(event.key.keysym, false);
            }
        }
    }

    void bindLuaObjects()
    {
        LuaBind::bindColor(m_lua->getState());
        LuaBind::bindVector(m_lua->getState());
        LuaBind::bindVideo(m_lua->getState());
        LuaBind::bindSystem(m_lua->getState());
        LuaBind::bindInput(m_lua->getState());
        LuaBind::bindKeys(m_lua->getState());
        luabridge::push(m_lua->getState(), m_video);
        lua_setglobal(m_lua->getState(), "Graphics");
        luabridge::push(m_lua->getState(), &m_system);
        lua_setglobal(m_lua->getState(), "System");
        luabridge::push(m_lua->getState(), &m_input);
        lua_setglobal(m_lua->getState(), "Input");
    }
};