#pragma once

#include "modulation/params.h"

class CuttingParams : public ModulationParams
{
public:
    CuttingParams() {}
    CuttingParams(const Config &conf)
        : ModulationParams(conf)
    {
        auto cut = conf["target_signal"];

        begin = cut["begin"];
        end = cut["end"];
    }

    double begin = 0;
    double end = 0;
};