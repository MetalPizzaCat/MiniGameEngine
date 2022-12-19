#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_framerate.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fmt/core.h>

#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Lua/LuaMachine.hpp"
#include "Log.hpp"
#include "Graphics/Video.hpp"
#include "System/System.hpp"
#include "System/Input.hpp"
#include "Content/ContentManager.hpp"
#include "Physics/Physics.hpp"
#include "Physics/PhysicsDebug.hpp"

/// @brief Class that handles SDL window and communication between parts of software
class Window
{
public:
    static const size_t canvasWidth = 1024;
    static const size_t canvasHeight = 1024;
    Window(int32_t width, int32_t height) : m_width(width),
                                            m_height(height),
                                            m_running(true),
                                            m_world(Vector2(0, 9.8f))

    {
        m_window = SDL_CreateWindow("Nema-Video v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        m_video = new Video(canvasWidth, canvasHeight, SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC));

        if (!m_window || !m_video->getRenderer())
        {
            Log::error("Failed to init window and renderer");
            exit(EXIT_FAILURE);
        }
        m_lua = new LuaMachine();
        bindLuaObjects();
        SDL_initFramerate(&m_fps);

        std::ofstream ofs;
        ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        m_manager.setRenderer(m_video->getRenderer());
        int result = IMG_Init(IMG_INIT_PNG);
        if (!(result == IMG_INIT_PNG))
        {
            Log::error(fmt::format("Failed to init SDL2_Image: {}", IMG_GetError()));
        }
        m_physicsDebug = new PhysicsDebugDraw(m_video);
        m_world.setDebugDraw(m_physicsDebug);
    }

    /// @brief Starts the game loop
    void run();

    LuaMachine *getLua() { return m_lua; }

    ~Window()
    {
        delete m_lua;
        delete m_physicsDebug;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        IMG_Quit();
        delete m_video;
    }

private:
    SDL_Window *m_window;
    /// @brief Width of the screen
    int32_t m_width;
    /// @brief Height of the screen
    int32_t m_height;
    bool m_running;
    LuaMachine *m_lua;
    Video *m_video;
    System m_system;
    Input m_input;
    FPSmanager m_fps;
    ContentManager m_manager;
    PhysicsWorld m_world;
    PhysicsDebugDraw *m_physicsDebug;
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

    void inputMouseLua(MouseEvent const &event);

    /// @brief Handle all of the window, keyboard and mouse events
    void handleEvents();

    void updatePhysics();

    /// @brief Bind all of the classes to the lua machine
    void bindLuaObjects();

    /// @brief Get mouse position relative to the window scaled to the video output size
    /// @return position
    Vector2 getMousePosition();

    /// @brief Get size of the physical window
    /// @return Window size
    Vector2 getWindowSize() const;

    /// @brief Set size of the physical window
    /// @param size New size
    void setWindowSize(Vector2 const &size);
};