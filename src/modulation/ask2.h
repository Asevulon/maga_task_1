#pragma once

#include <vector>

#include "modulation/params.h"
#include "modulation/make_signal.h"
#include "general/const.h"

template <typename T>
std::vector<T> generate_ask2(const Ask2Params &p, const std::function<T(double)> &make_signal)
{
    std::vector<T> res;

    size_t size_per_bit = p.Tb * p.fs;
    size_t size = p.bits.size() * size_per_bit;

    res.reserve(size);

    double df = 1. / (2. * p.Tb);
    double p_step = Pi2 * p.fc / p.fs;

    double phase = 0;
    double A = 0;

    for (const auto &c : p.bits)
    {
        A = (c - '0') ? p.A1 : p.A0;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res.emplace_back(make_signal(phase) * A);
            phase += p_step;
        }
    }
    return res;
}

inline std::vector<double> generate_ask2_double(const Ask2Params p)
{
    return generate_ask2<double>(p, make_signal_double);
}
inline std::vector<cmplx> generate_ask2_cmplx(const Ask2Params p)
{
    return generate_ask2<cmplx>(p, make_signal_cmplx);
}