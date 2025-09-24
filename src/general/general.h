#pragma once
#include <string>
#include <iostream>

inline int exec(const std::string cmd)
{
    std::cout << "exec: " << cmd << std::endl;
    return system(cmd.c_str());
}

inline double rand(double left, double right)
{
    return left + (right - left) * (double)std::rand() / (double)RAND_MAX;
}