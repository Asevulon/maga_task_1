#pragma once

#include <vector>
#include <functional>

#include "cmplx/cmplx.h"
#include "modulation/params.h"
#include "general/const.h"
#include "general/general.h"
#include "modulation/make_signal.h"

template <typename T>
std::vector<T> &apply_bpsk(
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

    double phase = 0;
    double p_step = Pi2 * fc / fs;

    for (size_t j = 0; j < bits.size(); ++j)
    {
        phase += (bits[j] - '0') ? Pi : 0;
        size_t offset = j * size_per_bit;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res[offset + i] = make_signal(phase);
            phase += p_step;
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
inline std::vector<T> generate_bpsk(
    double Tb,
    double fs,
    double fc,
    const std::string &bits,
    const std::function<T(double)> &make_signal)
{
    std::vector<T> res;
    return apply_bpsk<T>(res, Tb, fs, fc, bits, make_signal);
}
template <typename T>
inline std::vector<T> generate_bpsk(const BpskParams &p, const std::function<T(double)> &make_signal)
{
    return generate_bpsk<T>(p.Tb, p.fs, p.fc, random_bits(create_random(1).front(), p.bits), make_signal);
}
inline std::vector<double> generate_bpsk_double(const BpskParams p)
{
    return generate_bpsk<double>(p, make_signal_double);
}
inline std ::vector<cmplx> generate_bpsk_cmplx(const BpskParams p)
{
    return generate_bpsk<cmplx>(p, make_signal_cmplx);
}