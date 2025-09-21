#pragma once

#include "config/config.h"

#include <iostream>

class GeneratorParams
{
public:
    GeneratorParams(const Config &conf)
    {
        auto test = conf["test"];
        ampl = test["ampl"].get<double>();
        freq = test["freq"].get<double>();
        phase = test["phase"].get<double>();
        length = test["length"].get<double>();
        sample_rate = test["sample_rate"].get<double>();
        // print();
    }

    void print()
    {
        std::cout
            << "GeneratorParams:"
            << " ampl " << ampl
            << ", freq " << freq
            << ", phase " << phase
            << ", length " << length
            << ", sample_rate " << sample_rate
            << std::endl;
    }

    double ampl = 0;
    double freq = 0;
    double phase = 0;
    double length = 0;
    double sample_rate = 0;
};