#include "Log.hpp"
#include <iostream>

void Log::error(std::string error)
{
    std::cout << "Error: " << error << std::endl;
}