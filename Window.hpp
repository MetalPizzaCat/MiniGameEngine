#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_framerate.h>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
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
        SDL_initFramerate(&m_fps);

        std::ofstream ofs;
        ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    /// @brief Starts the game loop
    void run()
    {
        loadProject();
        m_lastUpdate = std::clock();
        while (m_running)
        {
            handleEvents();
            clearScreen();
            updateLua();
            render();
            SDL_framerateDelay(&m_fps);
            m_delta = (((float)(std::clock() - m_lastUpdate)) / CLOCKS_PER_SEC) * 1000.f;
            m_lastUpdate = std::clock();
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
    FPSmanager m_fps;
    /// @brief Amount of time passed since last frame. Default value is just random non zero value
    float m_delta = 0.000717;

    clock_t m_lastUpdate;

    bool loadProject()
    {
        std::ifstream file("project.lua");
        if (!file.is_open())
        {
            Log::error("Failed to open project");
            return false;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        LuaMachine projectConfig;
        std::string deb = buffer.str();
        projectConfig.loadCode(buffer.str().c_str());
        luabridge::LuaRef fileRef = luabridge::getGlobal(projectConfig.getState(), "main_file");
        if (!fileRef.isString())
        {
            return false;
        }
        const char *code = fileRef.cast<const char *>();
        std::ifstream codeFile(code);
        if (!file.is_open())
        {
            Log::error("Failed to main file");
            return false;
        }
        std::stringstream codeBuffer;
        codeBuffer << codeFile.rdbuf();
        return !m_lua->loadCode(codeBuffer.str().c_str()) && m_lua->call("_init");
    }

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
        if (!m_lua->call("_update", m_delta))
        {
            m_running = false;
        }
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
        Color::bindLua(m_lua->getState());
        Vector2::bindLua(m_lua->getState());
        Video::bindLua(m_lua->getState());
        System::bindLua(m_lua->getState());
        Input::bindInput(m_lua->getState());
        LuaBind::bindKeys(m_lua->getState());
        Log::bindLua(m_lua->getState());
        luabridge::push(m_lua->getState(), m_video);
        lua_setglobal(m_lua->getState(), "Graphics");
        luabridge::push(m_lua->getState(), &m_system);
        lua_setglobal(m_lua->getState(), "System");
        luabridge::push(m_lua->getState(), &m_input);
        lua_setglobal(m_lua->getState(), "Input");
    }
};