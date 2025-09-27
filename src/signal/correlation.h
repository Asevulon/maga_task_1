#pragma once

#include <vector>

#include "signal/params.h"

template <typename T>
std::vector<T> correlation(const std::vector<T> &x, const std::vector<T> &y)
{
    if (x.empty() || y.empty())
        return {};

    int N = x.size();
    int M = y.size();
    std::vector<T> res(N + M - 1);

    int left = -(M - 1);
    for (int k = left; k < N; ++k)
    {
        T sum = T{};
        for (int n = 0; n < M; ++n)
            sum += zero_border(x, k + n) * y[n];
        res[k - left] = sum;
    }

    T norma = std::sqrt(energy(x) * energy(y));
    for (auto &item : res)
        item /= norma;

    return res;
}

std::vector<double> generate_correlation_keys(const CorrelationKeyParams &p)
{
    std::vector<double> res;

    double dt = 1. / p.fs;
    double left = -p.begin + dt;
    std::cout << left;
    size_t size = p.Tb * p.bits.size() * p.fs;

    res.resize(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        res[i] = left + i * dt;
    }

    return res;
}