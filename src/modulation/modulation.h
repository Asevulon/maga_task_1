#pragma once
#include "modulation/bpsk.h"
#include "modulation/bfsk.h"
#include "modulation/ask2.h"
#include "scenario/params.h"

std::vector<double> generate_modulation_keys(const ModulationParams p);

std::vector<double> modulation(const Config &conf);
std::vector<cmplx> modulation_cmplx(const Config &conf);
void apply_modulation_exp(
    const std::string &mod,
    const double &Tb,
    const double &fs,
    const double &fc,
    const double &A0,
    const double &A1,
    const std::string &bits,
    std::vector<cmplx> &trg);