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
inline std::vector<T> cut(
    const std::vector<T> &src,
    const double &Tb,
    const double &fs,
    const size_t &bits_len,
    const double &begin,
    const double &end)
{
    double total_time = Tb * bits_len;
    size_t size = total_time * fs;
    size_t begin_idx = begin / total_time * size;
    size_t end_idx = end / total_time * size;
    return std::vector<T>(src.begin() + begin_idx, src.begin() + end_idx);
}
template <typename T>
inline size_t apply_cut(
    const std::vector<T> &src,
    std::vector<T> &trg,
    const double &Tb,
    const double &fs,
    const size_t &bits_len,
    const double &begin,
    const double &end)
{
    double total_time = Tb * bits_len;
    size_t size = total_time * fs;
    size_t begin_idx = begin / total_time * size;
    size_t end_idx = end / total_time * size;
    size_t trg_size = end_idx - begin_idx;
    if (trg.size() < trg_size)
        trg.resize(trg_size);
    for (size_t i = begin_idx; i < end_idx; ++i)
    {
        trg[i - begin_idx] = src[i];
    }
    for (size_t i = trg_size; i < trg.size(); ++i)
        trg[i] = T{};
    return trg_size;
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