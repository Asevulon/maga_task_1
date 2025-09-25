#pragma once

#include "modulation/params.h"
#include "scenario/params.h"

class CuttingParams : public ModulationParams, public TargetParams
{
public:
    CuttingParams() {}
    CuttingParams(const Config &conf)
        : ModulationParams(conf),
          TargetParams(conf) {}
};