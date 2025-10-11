#pragma once

#include <vector>

#include "modulation/params.h"
#include "general/const.h"
#include "modulation/make_signal.h"

template <typename T>
std::vector<T> &apply_bfsk(
    std::vector<T> &res,
    double Tb,
    double fs,
    double fc,
    const std::string &bits,
    const std::function<T(double)> &make_signal)
{

    double size_per_bit = fs / Tb;
    size_t size = bits.size() * size_per_bit;

    if (res.size() < size)
        res.resize(size);

    double df = Tb / 2.;
    double p_step_0 = Pi2 * (fc - df) / fs;
    double p_step_1 = Pi2 * (fc + df) / fs;

    double phase = 0;
    double d_phase = 0;

    for (size_t j = 0; j < bits.size(); ++j)
    {
        d_phase = (bits[j] - '0') ? p_step_1 : p_step_0;
        size_t offset = j * size_per_bit;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res[offset + i] = make_signal(phase);
            phase += d_phase;
        }
    }

    if (res.size() > size)
    {
        for (size_t i = size; i < res.size(); ++i)
            res[i] = T{};
    }
    return res;
}

template <typename T>
inline std::vector<T> generate_bfsk(
    double Tb,
    double fs,
    double fc,
    const std::string &bits,
    const std::function<T(double)> &make_signal)
{
    std::vector<T> res;
    return apply_bfsk(res, Tb, fs, fc, bits, make_signal);
}
template <typename T>
inline std::vector<T> generate_bfsk(const BfskParams &p, const std::function<T(double)> &make_signal)
{
    return generate_bfsk<T>(p.Tb, p.fs, p.fc, random_bits(create_random(1).front(), p.bits), make_signal);
}
inline std::vector<double> generate_bfsk_double(const BfskParams &p)
{
    return generate_bfsk<double>(p, make_signal_double);
}
inline std::vector<cmplx> generate_bfsk_cmplx(const BfskParams &p)
{
    return generate_bfsk<cmplx>(p, make_signal_cmplx);
}