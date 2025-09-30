#pragma once

#include "signal/params.h"

template <typename container>
inline double energy(container &&src)
{
    double res = 0;
    for (const auto &p : src)
        res += p * p;
    return res;
}

template <typename container>
inline container cut(container &src, const CuttingParams p)
{
    container res{};

    size_t size = p.bits.size() * p.Tb * p.fs;

    double total_time = p.Tb * p.bits.size();
    size_t begin = p.begin / total_time * size;
    size_t end = p.end / total_time * size;

    for (uint64_t i = begin; i < end; ++i)
    {
        res.emplace_back(*(src.begin() + i));
    }
    return res;
}

template <typename T>
inline size_t max_id(const std::vector<T> &src)
{
    size_t id = 0;
    size_t size = src.size();
    for (int i = 1; i < size; ++i)
    {
        if (src[id] < src[i])
            id = i;
    }
    return id;
}

inline double milliseconds(double val)
{
    return val * 1000;
}