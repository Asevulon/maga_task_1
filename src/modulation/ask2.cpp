#include "modulation/ask2.h"
#include "general/const.h"

std::vector<double> generate_ask2(const Ask2Params p)
{
    std::vector<double> res;

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
            res.emplace_back(A * sin(phase));
            phase += p_step;
        }
    }
    return res;
}