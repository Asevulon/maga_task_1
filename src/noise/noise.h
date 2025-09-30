#pragma once

#include <vector>

#include "noise/params.h"
#include "general/general.h"
#include "cmplx/cmplx.h"

std::vector<double> generate_white_noise(size_t size);
std::vector<double> apply_white_noise(std::vector<double> &target, const NoiseParams p);
std::vector<cmplx> apply_white_noise(std::vector<cmplx> &target, const NoiseParams &p);

inline double single_white_noise()
{
    double res = 0;
    for (int i = 0; i < 12; i++)
        res += rand(-1, 1);
    res /= 12;
    return res;
}

inline double convert_db(double val)
{
    return pow(10, val / 10);
}