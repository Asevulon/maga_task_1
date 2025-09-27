#pragma once

#include "cmplx/cmplx.h"

inline double make_signal_double(double phase)
{
    return sin(phase);
}
inline cmplx make_signal_cmplx(double phase)
{
    return cmplx(cos(phase), sin(phase));
}