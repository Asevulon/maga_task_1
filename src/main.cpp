#include <iostream>

#include "config/config.h"
#include "generator/generator.h"
#include "plot/plot.h"
#include "modulation/bpsk.h"

using std::cout;
using std::endl;

int main()
{
    auto conf = load_config("config.json");
    cout << "Config: " << conf << endl;

    auto signal = generate_signal(conf);
    auto keys = generate_signal_keys(conf);
    GnuplotParams p;
    draw_plot(keys, signal, p);

    signal = generate_bpsk(conf);
    keys = generate_bpsk_keys(conf);
    p.title = "bpsk";
    draw_plot(keys, signal, p);

    auto c_signal = generate_bpsk_cmplx(conf);
    auto re = cmplx_re(c_signal);
    auto im = cmplx_im(c_signal);
    GnuplotLineParams lp;
    lp.title = "cmplx bpsk";
    lp.lines.emplace_back("re", keys, re);
    // lp.lines.emplace_back("im", keys, im);
    draw_plot(lp);
    return 0;
}