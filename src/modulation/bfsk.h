#pragma once

#include <vector>

#include "modulation/params.h"
#include "general/const.h"
#include "modulation/make_signal.h"

template <typename T>
std::vector<T> generate_bfsk(const BfskParams &p, const std::function<T(double)> &make_signal)
{
    std::vector<T> res;

    size_t size_per_bit = p.Tb * p.fs;
    size_t size = p.bits.size() * size_per_bit;

    res.reserve(size);

    double df = 1. / (2. * p.Tb);
    double p_step_0 = Pi2 * (p.fc - df) / p.fs;
    double p_step_1 = Pi2 * (p.fc + df) / p.fs;

    double phase = 0;
    double d_phase = 0;

    for (const auto &c : p.bits)
    {
        d_phase = (c - '0') ? p_step_1 : p_step_0;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res.emplace_back(make_signal(phase));
            phase += d_phase;
        }
    }
    return res;
}

inline std::vector<double> generate_bfsk_double(const BfskParams p)
{
    return generate_bfsk<double>(p, make_signal_double);
}
inline std::vector<cmplx> generate_bfsk_cmplx(const BfskParams p)
{
    return generate_bfsk<cmplx>(p, make_signal_cmplx);
}