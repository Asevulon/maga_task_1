#pragma once

#include "modulation/modulation.h"
#include "signal/signal.h"
#include "noise/noise.h"
#include "signal/correlation.h"
#include "plot/plot_line.h"
#include "general/colors.h"

void correlation_scenario(const Config &conf)
{
    auto src = modulation_cmplx(conf);
    auto trg = cut(src, conf);

    auto src_n = apply_white_noise(src, conf["source"]);
    auto trg_n = apply_white_noise(trg, conf["target"]);

    auto src_keys = generate_modulation_keys(conf);
    auto trg_keys = cut(src_keys, conf);

    auto corr = correlation(src_n, trg_n);
    auto corr_abs = abs(corr);
    auto corr_keys = correlation_keys(src_n.size(), trg_n.size(), conf["modulation"]["fs"].get<double>(), trg_keys.front() - trg_keys.back());

    double corr_max = milliseconds(corr_keys[max_id(corr_abs)]);
    double error_rate = milliseconds(conf["modulation"]["Tb"]);
    double init_value = milliseconds(conf["target"]["begin"]);
    double diff = fabs(corr_max - init_value);
    bool success = diff < error_rate;

    std::cout
        << GREEN
        << "Max correlation detected in " << corr_max << "ms"
        << " with error rate " << error_rate << "ms.\n"
        << "The initial value is " << init_value << "ms.\n"
        << RESET;

    if (success)
    {
        std::cout
            << GREEN
            << "The signal was successfully detected with error " << diff << "ms.\n"
            << RESET;
    }
    else
    {
        std::cout
            << RED
            << "The error value is too high: " << diff << "ms.\n"
            << RESET;
    }

    GnuplotLineParams p;

    auto src_l = nline(src_keys, src);
    auto trg_l = nline(trg_keys, trg);
    auto src_n_l = nline(src_keys, src_n);
    auto trg_n_l = nline(trg_keys, trg_n);
    auto corr_abs_l = nline(corr_keys, corr_abs);

    p.title = "исходный";
    p.lines = {src_l};
    draw_plot(p);

    p.title = "исследуемый";
    p.lines = {trg_l};
    draw_plot(p);

    p.title = "исходный c шумом";
    p.lines = {src_n_l};
    draw_plot(p);

    p.title = "исследуемый c шумом";
    p.lines = {trg_n_l};
    draw_plot(p);

    p.title = "корреляция";
    p.lines = {corr_abs_l};
    draw_plot(p);
}
