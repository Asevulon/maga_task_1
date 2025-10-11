#pragma once

#include "config/config.h"

class SignalParams
{
public:
    SignalParams() {}
    SignalParams(const Config &conf)
    {
        noise = conf["Уровень шума, дБ"];
    }

    double noise = 0;
};

class SourceParams : public SignalParams
{
public:
    SourceParams() {};
    SourceParams(const Config &conf)
        : SignalParams(conf["Опорный сигнал"])
    {
        auto source = conf["Опорный сигнал"];

        mod = source["Тип модуляции"];
    }

    std::string mod{};
};

class TargetParams : public SignalParams
{
public:
    TargetParams() {};
    TargetParams(const Config &conf)
        : SignalParams(conf["Исследуемый сигнал"])
    {
        auto target = conf["Исследуемый сигнал"];

        begin = target["Начало, мс"].get<double>() / 1000.;
        end = target["Конец, мс"].get<double>() / 1000.;
    }

    double begin = 0;
    double end = 0;
};

class ExperimentParams
{
public:
    ExperimentParams() {};
    ExperimentParams(const Config &conf)
    {
        auto exp = conf["Параметры исследования устойчивости алгоритма"];
        noise_max = exp["Конечный уровень шума, дБ"];
        noise_min = exp["Начальный уровень шума, дБ"];
        noise_levels = exp["Количество шагов по шуму"];
        experiments_per_level = exp["Число повторений эксперимента"];
        threads = exp["Число потоков"];
    }
    double noise_max = 0;
    double noise_min = 0;
    uint64_t noise_levels = 0;
    uint64_t experiments_per_level = 0;
    uint64_t threads = 0;
};