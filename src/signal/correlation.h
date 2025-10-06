#pragma once

#include <vector>

#include "signal/params.h"
#include "cmplx/cmplx.h"

inline std::vector<cmplx> correlation(const std::vector<cmplx> &x, const std::vector<cmplx> &y)
{
    int Nx = x.size();
    int Ny = y.size();
    int Ncorr = Nx + Ny - 1;

    std::vector<cmplx> result(Ncorr, cmplx());

    for (int i = 0; i < Ncorr; ++i)
    {
        int k = i - Ny + 1;

        cmplx sum;

        // Суммируем по всем n, где оба индекса в пределах
        for (int n = 0; n < Ny; ++n)
        {
            int xn_index = n + k; // индекс в x: n + k

            if (xn_index >= 0 && xn_index < Nx)
            {
                sum = sum + x[xn_index] * conj(y[n]);
            }
        }

        result[i] = sum;
    }

    return result;
}

inline std::vector<double> correlation_keys(size_t x, size_t y, double fs, double begin)
{
    size_t size = x + y - 1;
    double dt = 1. / fs;
    std::vector<double> res;
    res.reserve(size);
    for (size_t i = 0; i < size; ++i)
    {
        res.emplace_back(begin + i * dt);
    }
    return res;
}

inline double correlation_key(
    const double &dt,
    const double &begin,
    const size_t &idx)
{
    return begin + idx * dt;
}

// request x.size() == y.size() == next_power_of_two(x.size() + y.size() - 1)
inline void correlation_fft(std::vector<cmplx> &x, std::vector<cmplx> &y, std::vector<cmplx> &r)
{
    fourea(x, -1);
    fourea(y, -1);
    size_t size = x.size();
    for (size_t i = 0; i < size; ++i)
    {
        r[i] = conj(x[i]) * y[i];
    }
    fourea(r, 1);
}