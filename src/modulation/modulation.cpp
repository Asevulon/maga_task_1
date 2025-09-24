#include "modulation/modulation.h"

std::vector<double> generate_modulation_keys(const BpskParams p)
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