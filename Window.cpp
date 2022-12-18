#include "Window.hpp"
#include "Graphics/Text.hpp"

bool Window::loadProject()
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
    try
    {
        return m_lua->loadCode(codeBuffer.str().c_str()) && m_lua->call("_init");
    }
    catch (luabridge::LuaException e)
    {
        Log::error(e.what());
        return false;
    }
}

void Window::clearScreen()
{
    m_video->clear();
}

void Window::render()
{
    m_video->draw(m_width, m_height);
}

void Window::updateLua()
{
    try
    {
        if (!m_lua->call("_update", m_delta))
        {
            m_running = false;
        }
    }
    catch (luabridge::LuaException e)
    {
        Log::error(e.what());
        m_running = false;
    }
}

void Window::handleEvents()
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

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int32_t x, y;
            SDL_GetMouseState(&x, &y);
            MouseState mouse = MouseState{
                .position = getMousePosition(),
                .button = event.button.button,
                .pressed = true,
                .clicks = event.button.clicks};
            m_input.setMouseButtonState((MouseButton)event.button.button, mouse);
            inputMouseLua(MouseEvent{.state = mouse, .eventType = (uint8_t)MouseEventType::Press});
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            int32_t x, y;
            SDL_GetMouseState(&x, &y);
            MouseState mouse = MouseState{
                .position = getMousePosition(),
                .button = event.button.button,
                .pressed = false,
                .clicks = event.button.clicks};
            m_input.setMouseButtonState((MouseButton)event.button.button, mouse);
            inputMouseLua(MouseEvent{.state = mouse, .eventType = (uint8_t)MouseEventType::Release});
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            MouseState mouse = MouseState{
                .position = getMousePosition(),
                .button = event.button.button,
                .pressed = event.button.state == SDL_PRESSED,
                .clicks = event.button.clicks};
            inputMouseLua(MouseEvent{.state = mouse, .eventType = (uint8_t)MouseEventType::Motion});
        }

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_GetWindowSize(m_window, &m_width, &m_height);
            }
        }
    }
}

void Window::run()
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

void Window::inputMouseLua(MouseEvent const &event)
{
    if (m_lua->isFunctionPresent("_mouseInput"))
    {
        m_lua->call("_mouseInput", event);
    }
}

Vector2 Window::getMousePosition()
{
    int32_t x, y;
    SDL_GetMouseState(&x, &y);
    int32_t windowWidth, windowHeight;
    SDL_GetWindowSize(m_window, &windowWidth, &windowHeight);
    float mouseY = (float)y * ((float)m_video->getHeight() / (float)windowHeight);
    float mouseX = ((float)x * ((float)m_video->getWidth() / (float)windowWidth));
    return Vector2(mouseX, mouseY);
}

Vector2 Window::getWindowSize() const
{
    return Vector2((float)m_width, (float)m_height);
}

void Window::setWindowSize(Vector2 const &size)
{
    SDL_SetWindowSize(m_window, (int32_t)size.x, (int32_t)size.y);
    m_width = (int32_t)size.x;
    m_height = (int32_t)size.y;
}

void Window::bindLuaObjects()
{
    luabridge::getGlobalNamespace(m_lua->getState())
        .beginClass<Window>("Window")
        .addFunction("get_size", &Window::getWindowSize)
        .addFunction("set_size", &Window::setWindowSize)
        .endClass();

    Color::bindLua(m_lua->getState());
    Vector2::bindLua(m_lua->getState());
    Video::bindLua(m_lua->getState());
    System::bindLua(m_lua->getState());
    Input::bindInput(m_lua->getState());
    LuaBind::bindKeys(m_lua->getState());
    Text::bindLua(m_lua->getState());
    Log::bindLua(m_lua->getState());
    MouseState::bindLua(m_lua->getState());
    MouseEvent::bindLua(m_lua->getState());
    ContentManager::bindLua(m_lua->getState());
    TextureResource::bindLua(m_lua->getState());
    luabridge::push(m_lua->getState(), m_video);
    lua_setglobal(m_lua->getState(), "Graphics");
    luabridge::push(m_lua->getState(), &m_system);
    lua_setglobal(m_lua->getState(), "System");
    luabridge::push(m_lua->getState(), &m_input);
    lua_setglobal(m_lua->getState(), "Input");
    luabridge::push(m_lua->getState(), &m_manager);
    lua_setglobal(m_lua->getState(), "ContentManager");
    luabridge::push(m_lua->getState(), this);
    lua_setglobal(m_lua->getState(), "Window");
}