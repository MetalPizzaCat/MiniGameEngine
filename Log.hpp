#pragma once

namespace Log
{
    void error(std::string error)
    {
        std::cout << "Error: " << error << std::endl;
    }
}