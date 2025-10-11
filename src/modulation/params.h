#pragma once

#include "config/config.h"

class ModulationParams
{
public:
    ModulationParams() {}
    ModulationParams(const Config &conf)
    {
        auto mod = conf["Опорный сигнал"];

        bits = mod["Число бит в сигнале"].get<size_t>();
        fc = 1000. * mod["Несущая частота, кГц"].get<double>();
        Tb = mod["Битовая скорость, бит/с"].get<double>();
        fs = 1000. * mod["Частота дискретизации, кГЦ"].get<double>();
    }

    size_t bits = 0;
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
        auto ask2 = conf["Опорный сигнал"]["Модуляция ask2"];

        A0 = ask2["Уровень для 0"].get<double>();
        A1 = ask2["Уровень для 1"].get<double>();
    }

    double A0 = 0;
    double A1 = 0;
};