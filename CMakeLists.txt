cmake_minimum_required(VERSION 3.0.0)
project(MiniGameEngine  VERSION 0.1.0)

set(ENGINE_DEFAULT_FONT_NAME Roboto-Medium.ttf)
add_compile_definitions(DEFAULT_FONT_NAME="${ENGINE_DEFAULT_FONT_NAME}")
# How big is the default font
add_compile_definitions(DEFAULT_FONT_SIZE=32)
# Defines how much pixels make up 1m. For example PHYSICS_SCALE=64 means 1m = 64 pixels
add_compile_definitions(PHYSICS_SCALE=128.f)
#comment this line out or remove it to build without using SDL2_GFX
add_compile_definitions(USE_SDL2_GFX)
# uncomment this to prevent fatal crashes from displaying error messages and just watch OS handle c++ exceptions itself instead
#add_compile_definitions(SILENT_FAILURE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set( CMAKE_VERBOSE_MAKEFILE on )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Box2D REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(LuaBridgeLib)
include_directories(nema-video ${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIRS})
add_executable(MiniGameEngine 
    main.cpp
    Window.hpp
    Window.cpp
    Log.hpp
    Log.cpp
    Lua/LuaMachine.hpp 
    Lua/LuaMachine.cpp
    Graphics/Video.hpp
    Graphics/Video.cpp
    System/System.hpp
    System/System.cpp
    Graphics/Color.hpp
    Graphics/Color.cpp
    Graphics/Vector.hpp
    Graphics/Vector.cpp
    System/Input.hpp
    System/Input.cpp
    System/Mouse.hpp
    System/Mouse.cpp
    Graphics/Texture.hpp
    Graphics/Texture.cpp
    Graphics/Text.hpp
    Graphics/Text.cpp
    Content/ContentManager.hpp
    Content/ContentManager.cpp
    Content/TextureResource.hpp
    Content/TextureResource.cpp
    Physics/PhysicsWorld.hpp
    Physics/PhysicsWorld.cpp
    Physics/PhysicsBody.hpp
    Physics/PhysicsBody.cpp
    Physics/ColliderShape.hpp
    Physics/ColliderShape.cpp
    Physics/Physics.hpp
    Physics/Physics.cpp
    Physics/PhysicsDebug.hpp
    Physics/PhysicsDebug.cpp
    Physics/CollisionCallback.hpp
    Physics/CollisionCallback.cpp
    )

target_link_libraries(MiniGameEngine  PRIVATE LuaBridge SDL2_image SDL2_ttf SDL2_gfx lua dl fmt::fmt Box2D ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

configure_file(Fonts/${ENGINE_DEFAULT_FONT_NAME} Fonts/${ENGINE_DEFAULT_FONT_NAME} COPYONLY)
configure_file(Fonts/OFL.txt Fonts/OFL.txt COPYONLY)
