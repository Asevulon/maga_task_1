#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <random>

inline int exec(const std::string cmd)
{
    std::cout << "exec: " << cmd << std::endl;
    return system(cmd.c_str());
}

inline double rand(double left, double right)
{
    return left + (right - left) * (double)std::rand() / (double)RAND_MAX;
}

inline std::vector<std::mt19937> create_random(uint64_t n)
{
    std::vector<std::mt19937> generators;
    std::random_device rd;
    std::seed_seq base_seed{rd(), rd(), rd(), rd()};
    std::vector<unsigned> seeds(n);
    base_seed.generate(seeds.begin(), seeds.end());
    for (int i = 0; i < n; ++i)
    {
        generators.emplace_back(seeds[i]);
    }

    return generators;
}

inline std::string random_bits(std::mt19937 &gen, const size_t &size)
{
    std::uniform_int_distribution<uint8_t> dist('0', '1');
    std::string bits;
    bits.resize(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        bits[i] = dist(gen);
    }
    return bits;
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
