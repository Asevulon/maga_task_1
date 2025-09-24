#include "noise/noise.h"

#include <cstdint>

#include "signal/signal.h"

std::vector<double> generate_white_noise(size_t size)
{
    std::vector<double> res;
    res.reserve(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        res.emplace_back(single_white_noise());
    }
    return res;
}
std::vector<double> apply_white_noise(std::vector<double> &target, const NoiseParams p)
{
    auto size = target.size();
    auto n = generate_white_noise(size);
    auto en = energy(n);
    auto es = energy(target);
    double betta = sqrt(p.level * es / en);
    std::vector<double> res;
    res.reserve(size);
    for (uint64_t i = 0; i < size; ++i)
    {
        res.emplace_back(target[i] + betta * n[i]);
    }
    return res;
}