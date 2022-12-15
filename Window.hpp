#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_framerate.h>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Lua/LuaMachine.hpp"
#include "Log.hpp"
#include "Graphics/Video.hpp"
#include "System/System.hpp"
#include "System/Input.hpp"

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
        SDL_initFramerate(&m_fps);

        std::ofstream ofs;
        ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    /// @brief Starts the game loop
    void run();

    LuaMachine *getLua() { return m_lua.get(); }

    ~Window()
    {
        SDL_DestroyWindow(m_window);
        delete m_video;
    }

private:
    SDL_Window *m_window;
    /// @brief Width of the screen
    int32_t m_width;
    /// @brief Height of the screen
    int32_t m_height;
    bool m_running;
    std::unique_ptr<LuaMachine> m_lua;
    Video *m_video;
    System m_system;
    Input m_input;
    FPSmanager m_fps;
    /// @brief Amount of time passed since last frame. Default value is just random non zero value
    float m_delta = 0.000717;
    /// @brief Clock fo storing last time when update happened
    clock_t m_lastUpdate;

    /// @brief Load project info from project.lua file
    /// @return true if project was successfully loaded
    bool loadProject();

    /// @brief Clears current screen
    void clearScreen();
    
    /// @brief Render everything to the screen
    void render();

    /// @brief Execute update sequence in lua code
    void updateLua();

    /// @brief Handle all of the window, keyboard and mouse events
    void handleEvents();

    /// @brief Bind all of the classes to the lua machine
    void bindLuaObjects();
};