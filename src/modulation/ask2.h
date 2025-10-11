#pragma once

#include <vector>

#include "modulation/params.h"
#include "modulation/make_signal.h"
#include "general/const.h"

template <typename T>
std::vector<T> &apply_ask2(
    std::vector<T> &res,
    double Tb,
    double fs,
    double fc,
    double A0,
    double A1,
    const std::string &bits,
    const std::function<T(double)> &make_signal)
{

    size_t size_per_bit = Tb * fs;
    size_t size = bits.size() * size_per_bit;

    if (res.size() < size)
        res.resize(size);

    double df = 1. / (2. * Tb);
    double p_step = Pi2 * fc / fs;

    double phase = 0;
    double A = 0;

    for (size_t j = 0; j < bits.size(); ++j)
    {
        A = (bits[j] - '0') ? A1 : A0;
        size_t offset = j * size_per_bit;
        for (uint64_t i = 0; i < size_per_bit; ++i)
        {
            if (phase > Pi2)
                phase -= Pi2;
            res[offset + i] = make_signal(phase) * A;
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
inline std::vector<T> generate_ask2(
    double Tb,
    double fs,
    double fc,
    double A0,
    double A1,
    const std::string &bits,
    const std::function<T(double)> &make_signal)
{
    std::vector<T> res;
    return apply_ask2<T>(res, Tb, fs, fc, A0, A1, bits, make_signal);
}
template <typename T>
inline std::vector<T> generate_ask2(const Ask2Params &p, const std::function<T(double)> &make_signal)
{
    return generate_ask2<T>(p.Tb, p.fs, p.fc, p.A0, p.A1, p.bits, make_signal);
}
inline std::vector<double> generate_ask2_double(const Ask2Params p)
{
    return generate_ask2<double>(p, make_signal_double);
}
inline std::vector<cmplx> generate_ask2_cmplx(const Ask2Params p)
{
    return generate_ask2<cmplx>(p, make_signal_cmplx);
}