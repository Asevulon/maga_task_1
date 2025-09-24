#pragma once

#include "config/config.h"

class NoiseParams
{
public:
    NoiseParams(const Config &conf)
    {
        auto noise = conf["noise"];

        level = noise["level"];
    }

    double level = 0;
};