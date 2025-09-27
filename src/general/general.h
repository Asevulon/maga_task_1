#pragma once
#include <string>
#include <iostream>
#include <vector>

inline int exec(const std::string cmd)
{
    std::cout << "exec: " << cmd << std::endl;
    return system(cmd.c_str());
}

inline double rand(double left, double right)
{
    return left + (right - left) * (double)std::rand() / (double)RAND_MAX;
}

template <typename T>
inline std::vector<double> autokeys(T &&src)
{
    std::vector<double> keys;
    keys.resize(src.size());
    for (uint64_t i = 0; i < keys.size(); ++i)
        keys[i] = i;
    return keys;
}
