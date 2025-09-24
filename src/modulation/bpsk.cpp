#include "modulation/bpsk.h"
#include "general/const.h"

#include <iostream>
#include "bpsk.h"

std::vector<double> generate_bpsk(const BpskParams p)
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
            if (phase > Pi2)
                phase -= Pi2;
            res.push_back(sin(phase));
            phase += p_step;
        }
    }
    return res;
}

std::vector<cmplx> generate_bpsk_cmplx(const BpskParams p)
{
    std::vector<cmplx> res;

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
            res.emplace_back(cos(phase), sin(phase));
            phase += p_step;
        }
    }
    return res;
}
