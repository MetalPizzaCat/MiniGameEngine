# MiniGameEngine
A small engine for small games by Veronika "MetalPizzaCat"

## Simple and small
The engine is aimed to be as small as possible while still offering enough tools for making games and graphics applications.<br/>
It provides most basic tools for loading content into the engine as well as input and drawing capabilities

## Lua 
The engine is designed not around c++ and it's style of OOP but rather around Lua and making it as simple as possible to extend engine from Lua itself.
Lua was chosen for being both simplistic and very powerful as well as being easy to integrate with c++ code.

## Dependencies
Engine uses 
| Library    | Version                 | Link                                      | Notes                                             |
|------------|-------------------------|-------------------------------------------|---------------------------------------------------|
| SDL2       | 2.0.10                  | https://www.libsdl.org/                   |                                                   |
| SDL2-image | 2.0.5                   | https://github.com/libsdl-org/SDL_image   |                                                   |
| SDl2-ttf   | 2.0.15                  | https://github.com/libsdl-org/SDL_ttf     |                                                   |
| SDL2_gfx   | 1.0.4                   | https://sourceforge.net/projects/sdl2gfx/ | Used for helper drawing functions, can be removed |
| Lua        | 5.4                     | https://www.lua.org/                      |                                                   |
| fmt        | Latest in official repo | https://github.com/fmtlib/fmt.git         |                                                   |

## Getting the engine
All of the engine dependencies must be installed. Building the engine just requires to use `cmake build`

## Running projects
* Create file `project.lua` in the same folder as the executable
* Add `main_file = "FILENAME"` line to the file where FILENAME is path to the main lua file of the project
### Notes about projects
* Main lua file must have `_update` and `_init` functions
* `Graphics`,`Input` and `ContentManager` are singletons that are created from c++ code even before project code gets loaded. They are objects that directly interact with underlying systems and only expose some functionality to Lua. Creating a copy of them will lead to undefined behavior/

## Documentation
Coming soon, probably :)

## Examples 
### Hello world
```lua
-- Init function is called after script is loaded and before update
-- Because of the way lua is loaded code can just be written outside of any function and it will get executed on load as well
function _init()
    --print is used for debug
    print("hello world")
end

-- Main function of the project. Called every frame with delta being time since last frame in seconds
function _update(delta)
end
```

### *Fancy* hello world
Draws text to screen using built-in helper function
```lua
function _init()
end

-- Main function of the project. Called every frame with delta being time since last frame in seconds
function _update(delta)
    -- This will write "hello world!" at 0,0 coordinates of the screen with white colour
    -- Graphics is main graphics object of the engine responsible for all of the drawing
    -- this method creates and deletes textures used for text every time it's called so it's not exactly efficient
    Graphics:draw_text(Vector2(0,0),"hello world!",Color(255,255,255))
end
```

### *Fancier* hello world
Draws text to screen using dedicated object
```lua
function _init()
end

-- Create new text object that will create text texture only once and reuse it each time it's called
local text = Text(Graphics, "Hello, world!", Color(255, 255, 255), Vector2(0, 0))
-- Main function of the project. Called every frame with delta being time since last frame in seconds
function _update(delta)
    -- Text object has function that draws text without needing to use Graphics object directly
    text:draw()
end
```