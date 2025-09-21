#pragma once
#include <string>
#include <iostream>

inline int exec(const std::string cmd)
{
    std::cout << "exec: " << cmd << std::endl;
    return system(cmd.c_str());
}