#pragma once

#include "scenario/params.h"

class NoiseParams : public SignalParams
{
public:
    NoiseParams() {}
    NoiseParams(const Config &conf)
        : SignalParams(conf) {}
};