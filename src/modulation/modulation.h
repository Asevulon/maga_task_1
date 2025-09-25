#pragma once
#include "modulation/bpsk.h"
#include "modulation/bfsk.h"
#include "modulation/ask2.h"
#include "scenario/params.h"

std::vector<double> generate_modulation_keys(const ModulationParams p);

std::vector<double> modulation(const Config &conf);