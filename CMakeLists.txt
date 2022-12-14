cmake_minimum_required(VERSION 3.0.0)
project(MiniGameEngine  VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

set( CMAKE_VERBOSE_MAKEFILE on )

find_package(SDL2 REQUIRED)

include(CTest)
enable_testing()

add_subdirectory(LuaBridgeLib)
include_directories(nema-video ${SDL2_INCLUDE_DIRS})
add_executable(MiniGameEngine 
    main.cpp
    Window.hpp
    Window.cpp
    Log.hpp
    Log.cpp
    LuaMachine.hpp 
    LuaMachine.cpp
    Video.hpp
    Video.cpp
    System.hpp
    System.cpp
    Color.hpp
    Color.cpp
    Vector.hpp
    Vector.cpp
    Input.hpp
    Input.cpp
    )

target_link_libraries(MiniGameEngine  PRIVATE LuaBridge SDL2_gfx lua dl fmt::fmt ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
