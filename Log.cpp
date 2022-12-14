#define MINI_ENGINE_LOG_FILE

#include "Log.hpp"
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

#ifdef MINI_ENGINE_LOG_FILE
#include <fstream>
#endif

void Log::error(std::string error)
{
    fmt::print(fg(fmt::color::red), "Error: {}\n", error);
#ifdef MINI_ENGINE_LOG_FILE
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << "Error: "
            << error<< std::endl;
#endif
}

void Log::info(std::string error)
{
    fmt::print(fg(fmt::color::blue), "Info: {}\n", error);
#ifdef MINI_ENGINE_LOG_FILE
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << "Info: "
            << error<< std::endl;
#endif
}

void Log::print(std::string info)
{
    std::cout << info << std::endl;
#ifdef MINI_ENGINE_LOG_FILE
    std::ofstream outfile;
    outfile.open("log.txt", std::ios_base::app); // append instead of overwrite
    outfile << info << std::endl;
#endif
}

void Log::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
        .addFunction("error", &Log::error)
        .addFunction("info", &Log::info)
        .addFunction("print", &Log::print);
}