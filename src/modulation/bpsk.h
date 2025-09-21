#pragma once

#include <vector>

#include "modulation/params.h"

std::vector<double> generate_bpsk(BpskParams params);
std::vector<double> generate_bpsk_keys(const BpskParams p);
