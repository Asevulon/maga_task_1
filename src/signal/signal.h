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

template <typename Container>
inline auto zero_border(Container &&src, int idx)
{
    using T = typename std::decay_t<Container>::value_type;
    return ((idx >= 0) && (idx < src.size())) ? src[idx] : T{};
}