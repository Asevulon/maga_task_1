#include "config.h"
#include <fstream>

Config load_config(std::string path)
{
    std::ifstream file(path);
    Config conf;
    file >> conf;
    return conf;
}
