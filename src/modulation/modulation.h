#pragma once
#include "modulation/bpsk.h"
#include "modulation/bfsk.h"
#include "modulation/ask2.h"

std::vector<double> generate_modulation_keys(const BpskParams p);
