#pragma once

template <typename container>
inline double energy(container &&src)
{
    double res = 0;
    for (const auto &p : src)
        res += p * p;
    return res;
}