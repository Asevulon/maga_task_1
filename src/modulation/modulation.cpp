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
        return generate_bpsk(conf);

    if (p.mod == "bfsk")
        return generate_bfsk(conf);

    if (p.mod == "ask2")
        return generate_ask2(conf);

    throw std::runtime_error("unknown modulation mode");
}