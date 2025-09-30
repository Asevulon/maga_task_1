#include "modulation/modulation.h"

#include <iostream>

std::vector<double> generate_modulation_keys(const ModulationParams p)
{
    size_t size = p.bits.size() * p.Tb * p.fs;
    std::vector<double> res;
    res.resize(size);
    double dt = 1. / p.fs;
    for (uint64_t i = 0; i < size; ++i)
    {
        res[i] = dt * i;
    }
    return res;
}

std::vector<double> modulation(const Config &conf)
{
    SourceParams p = conf;

    if (p.mod == "bpsk")
        return generate_bpsk_double(conf);

    if (p.mod == "bfsk")
        return generate_bfsk_double(conf);

    if (p.mod == "ask2")
        return generate_ask2_double(conf);

    throw std::runtime_error("unknown modulation mode");
}

std::vector<cmplx> modulation_cmplx(const Config &conf)
{
    SourceParams p = conf;

    if (p.mod == "bpsk")
        return generate_bpsk_cmplx(conf);

    if (p.mod == "bfsk")
        return generate_bfsk_cmplx(conf);

    if (p.mod == "ask2")
        return generate_ask2_cmplx(conf);

    throw std::runtime_error("unknown modulation mode");
}

std::vector<cmplx> modulation_exp(
    const std::string &mod,
    const double &Tb,
    const double &fs,
    const double &fc,
    const double &A0,
    const double &A1,
    const std::string &bits)
{
    if (mod == "bpsk")
        return generate_bpsk<cmplx>(Tb, fs, fc, bits, make_signal_cmplx);

    if (mod == "bfsk")
        return generate_bfsk<cmplx>(Tb, fs, fc, bits, make_signal_cmplx);

    if (mod == "ask2")
        return generate_ask2<cmplx>(Tb, fs, fc, A0, A1, bits, make_signal_cmplx);

    throw std::runtime_error("unknown modulation mode");
}