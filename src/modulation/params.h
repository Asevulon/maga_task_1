#pragma once

#include "config/config.h"

class ModulationParams
{
public:
    ModulationParams() {}
    ModulationParams(const Config &conf)
    {
        auto mod = conf["modulation"];

        bits = mod["bits"].get<std::string>();
        fc = mod["fc"].get<double>();
        Tb = mod["Tb"].get<double>();
        fs = mod["fs"].get<double>();
    }

    std::string bits;
    double fc = 0;
    double Tb = 0;
    double fs = 0;
};

class BpskParams : public ModulationParams
{
public:
    BpskParams() {}
    BpskParams(const Config &conf)
        : ModulationParams(conf) {}
};

class BfskParams : public ModulationParams
{
public:
    BfskParams() {}
    BfskParams(const Config &conf)
        : ModulationParams(conf) {}
};

class Ask2Params : public ModulationParams
{
public:
    Ask2Params() {}
    Ask2Params(const Config &conf)
        : ModulationParams(conf)
    {
        auto ask2 = conf["modulation"]["ask2"];

        A0 = ask2["A0"].get<double>();
        A1 = ask2["A1"].get<double>();
    }

    double A0 = 0;
    double A1 = 0;
};