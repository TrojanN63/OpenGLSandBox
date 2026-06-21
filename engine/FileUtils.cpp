#include "FileUtils.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string readFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Nao foi possivel abrir: " + path
        );
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
