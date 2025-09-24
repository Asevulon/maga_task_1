#pragma once

#include <vector>
#include "cmplx/cmplx.h"

#include "modulation/params.h"

std::vector<double> generate_bpsk(const BpskParams params);

std::vector<cmplx> generate_bpsk_cmplx(const BpskParams p);