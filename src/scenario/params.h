#pragma once

#include "config/config.h"

class SignalParams
{
public:
    SignalParams() {}
    SignalParams(const Config &conf)
    {
        noise = conf["noise"];
    }

    double noise = 0;
};

class SourceParams : public SignalParams
{
public:
    SourceParams() {};
    SourceParams(const Config &conf)
        : SignalParams(conf["source"])
    {
        auto source = conf["source"];

        mod = source["mod"];
    }

    std::string mod{};
};

class TargetParams : public SignalParams
{
public:
    TargetParams() {};
    TargetParams(const Config &conf)
        : SignalParams(conf["target"])
    {
        auto target = conf["target"];

        begin = target["begin"];
        end = target["end"];
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
        auto exp = conf["experiment"];
        noise_max = exp["noise_max"];
        noise_min = exp["noise_min"];
        noise_levels = exp["noise_levels"];
        experiments_per_level = exp["experiment_per_level"];
        bits_len = exp["bits_len"];
        threads = exp["threads"];
    }
    double noise_max = 0;
    double noise_min = 0;
    uint64_t noise_levels = 0;
    uint64_t experiments_per_level = 0;
    size_t bits_len = 0;
    uint64_t threads = 0;
};