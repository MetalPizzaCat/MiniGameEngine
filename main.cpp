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
        Graphics:clear()
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
        
    end
)";
int main(int, char **)
{
    Window win(600, 600);
    win.run(g_code);

    return EXIT_FAILURE;
}
