#pragma once

#include "modulation/modulation.h"
#include "signal/signal.h"
#include "noise/noise.h"
#include "signal/correlation.h"
#include "plot/plot.h"

void correlation_scenario(const Config &conf)
{
    auto src = modulation(conf);
    auto trg = cut(src, conf);

    auto src_n = apply_white_noise(src, conf["source"]);
    auto trg_n = apply_white_noise(trg, conf["target"]);

    auto keys = generate_modulation_keys(conf);

    auto corr = correlation(src_n, trg_n);
    auto corr_keys = generate_correlation_keys(conf);

    GnuplotLine src_l = {"src", merge(keys, src)};
    GnuplotLine trg_l = {"trg", merge(keys, trg)};
    GnuplotLine src_n_l = {"src_n", merge(keys, src_n)};
    GnuplotLine trg_n_l = {"trg_n", merge(keys, trg_n)};
    GnuplotLine corr_l = {"corr", merge(corr_keys, corr)};

    GnuplotLineParams p;

    p.title = "исходный";
    p.lines = {src_l};
    draw_plot(p);

    p.title = "исследуемый";
    p.lines = {trg_l};
    draw_plot(p);

    p.title = "исходный c шумом";
    p.lines = {src_l, src_n_l};
    draw_plot(p);

    p.title = "исследуемый c шумом";
    p.lines = {trg_l, trg_n_l};
    draw_plot(p);

    p.title = "корреляция";
    p.lines = {corr_l};
    draw_plot(p);
}
