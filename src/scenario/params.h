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