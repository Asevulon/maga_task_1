#include "modulation/bpsk.h"
#include "general/const.h"

#include <iostream>

std::vector<double> generate_bpsk(BpskParams p)
{
    std::vector<double> res;

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
            if (phase > Pi)
                phase -= Pi2;
            res.push_back(sin(phase));
            // res.push_back((c - '0') ? -sin(phase) : sin(phase));
            phase += p_step;
        }
    }
    return res;
}

std::vector<double> generate_bpsk_keys(const BpskParams p)
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
