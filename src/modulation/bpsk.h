#pragma once

#include <vector>
#include <functional>

#include "cmplx/cmplx.h"
#include "modulation/params.h"
#include "general/const.h"
#include "modulation/make_signal.h"

template <typename T>
std::vector<T> generate_bpsk(const BpskParams &p, const std::function<T(double)> &make_signal)
{
    std::vector<T> res;

    size_t size_per_bit = p.Tb * p.fs;
    size_t size = p.bits.size() * size_per_bit;

    res.reserve(size);

    double phase = 0;
    double p_step = Pi2 * p.fc / p.fs;

    for (auto &c : p.bits)
    {
        phase += (c - '0') ? Pi : 0;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res.emplace_back(make_signal(phase));
            phase += p_step;
        }
    }
    return res;
}

inline std::vector<double> generate_bpsk_double(const BpskParams p)
{
    return generate_bpsk<double>(p, make_signal_double);
}
inline std ::vector<cmplx> generate_bpsk_cmplx(const BpskParams p)
{
    return generate_bpsk<cmplx>(p, make_signal_cmplx);
}