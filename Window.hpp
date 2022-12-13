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
                                            m_running(true)

    {
        m_window = SDL_CreateWindow("Nema-Video v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        m_video = new Video(canvasWidth, canvasHeight, SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED));

        if (!m_window || !m_video->getRenderer())
        {
            Log::error("Failed to init window and renderer");
            exit(EXIT_FAILURE);
        }
        m_lua = std::make_unique<LuaMachine>();
        bindLuaObjects();
    }

    /// @brief Starts the game loop
    void run(const char *code)
    {
        if (!m_lua->loadCode(code) && m_lua->call("_init"))
        {
            return;
        }
        while (m_running)
        {
            handleEvents();
            clearScreen();
            updateLua();
            render();
        }
    }

    LuaMachine *getLua() { return m_lua.get(); }

    ~Window()
    {
        SDL_DestroyWindow(m_window);
        delete m_video;
    }

private:
    SDL_Window *m_window;
    int32_t m_width;
    int32_t m_height;
    bool m_running;
    std::unique_ptr<LuaMachine> m_lua;
    Video *m_video;
    System m_system;
    Input m_input;
    /// @brief Last time when clock was updated
    std::chrono::high_resolution_clock m_tick;

    void clearScreen()
    {
        m_video->clear();
    }

    void render()
    {
        m_video->draw(m_width, m_height);
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