#pragma once

#include "config/config.h"

class BpskParams
{
public:
    BpskParams(const Config &conf)
    {
        auto bpsk = conf["bpsk"];

        bits = bpsk["bits"].get<std::string>();
        fc = bpsk["fc"].get<double>();
        Tb = bpsk["Tb"].get<double>();
        fs = bpsk["fs"].get<double>();
    }

    std::string bits;
    double fc = 0;
    double Tb = 0;
    double fs = 0;
};
