#pragma once

#include "scenario/params.h"
#include "modulation/modulation.h"
#include "signal/signal.h"
#include "general/general.h"
#include "noise/noise.h"
#include "signal/correlation.h"

double single_experiment(
    std::mt19937 &gen,
    const size_t &bits_len,
    const std::string &mod,
    const Ask2Params &mp,
    const CuttingParams &cp,
    const double &noise_source,
    const double &noise_target)
{
    std::string bits = random_bits(gen, bits_len);
    auto src = modulation_exp(mod, mp.Tb, mp.fs, mp.fc, mp.A0, mp.A1, bits);
    auto trg = cut(src, mp.Tb, mp.fs, bits_len, cp.begin, cp.end);

    apply_white_noise_raw(src, noise_source);
    apply_white_noise_raw(trg, noise_target);

    auto corr = correlation(src, trg);
    auto corr_abs = abs(corr);
    return correlation_key(1. / mp.fs, , max_id(corr_abs));
}

void experiment(const Config &conf)
{
    ExperimentParams exp_p = conf;

    auto generators = create_random(exp_p.threads);

    double noise_step = (exp_p.noise_max - exp_p.noise_min) / double(exp_p.noise_levels - 1);
}