#include <iostream>

#include "Window.hpp"

using namespace luabridge;

const char *const g_code = R"(
    --called before everything get initalized
    local pos = Vector2(10,10)
    Input:is_physical_key_pressed(KEY_PHYS_DOWN)
    function _init()
        System:print("this is when setup will happen")
    end
    function _update()
        --Graphics:clear()
        if Input:is_physical_key_pressed(KEY_PHYS_DOWN) == true then
            pos.x = pos.y + 1
        elseif Input:is_physical_key_pressed(KEY_PHYS_UP) == true then
            pos.x = pos.y - 1
        end
        if Input:is_physical_key_pressed(KEY_PHYS_LEFT)  == true then
            pos.x = pos.x + 1
        elseif Input:is_physical_key_pressed(KEY_PHYS_RIGHT)  == true then
            pos.x = pos.x - 1
        end
        Graphics:draw_point(pos,Color(255,255,0))
        Graphics:draw_rect(Vector2(50,0),Vector2(50,50),Color(255,0,0))
        Graphics:draw_rect(Vector2(50,50),Vector2(Graphics.screen_width,50),Color(255,0,0))
        Graphics:draw_circle(Vector2(60,150),10,Color(0,0,255))
    end
)";

int main(int, char **)
{
#ifdef SILENT_FAILURE
    try
    {
        Window win(600, 600);
        win.run();
        return EXIT_SUCCESS;
    }
    catch (luabridge::LuaException e)
    {
        Log::error(e.what());
        return EXIT_FAILURE;
    }
    catch (std::exception e)
    {
        Log::error(e.what());
        return EXIT_FAILURE;
    }
#else
    Window win(600, 600);
    win.run();
    return EXIT_SUCCESS;
#endif
}
