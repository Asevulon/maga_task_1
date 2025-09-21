#include "generator/generator.h"
#include "general/const.h"

std::vector<double> generate_signal(const GeneratorParams p)
{
    std::vector<double> signal;

    uint64_t size = p.length * p.sample_rate + 1;
    signal.resize(size);

    double phase = p.phase;
    double p_step = Pi2 * p.freq / p.sample_rate;

    for (uint64_t i = 0; i < size; ++i)
    {
        phase = (phase > Pi2) ? phase - Pi2 : phase;
        signal[i] = p.ampl * sin(phase);
        phase += p_step;
    }

    return signal;
}

std::vector<double> generate_signal_keys(const GeneratorParams p)
{
    std::vector<double> keys;

    uint64_t size = p.length * p.sample_rate + 1;
    keys.resize(size);

    double dt = 1. / p.sample_rate;

    for (uint64_t i = 0; i < size; ++i)
        keys[i] = i * dt;

    return keys;
}
