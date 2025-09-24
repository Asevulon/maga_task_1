#include <iostream>

#include "config/config.h"
#include "generator/generator.h"
#include "plot/plot.h"
#include "modulation/modulation.h"
#include "noise/noise.h"

using std::cout;
using std::endl;

int main()
{
    auto conf = load_config("config.json");
    cout << "Config: " << conf << endl;

    auto signal = generate_bpsk(conf);
    auto keys = generate_modulation_keys(conf);
    auto noised = apply_white_noise(signal, conf);

    GnuplotLineParams p;
    p.title = "noised check";
    p.lines = {
        // {"signal", merge(keys, signal)},
        {"noised", merge(keys, noised)}};
    draw_plot(p);
    return 0;
}