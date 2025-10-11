#pragma once

#include "modulation/modulation.h"
#include "signal/signal.h"
#include "noise/noise.h"
#include "plot/plot.h"

void generation(const Config &conf)
{
    auto src = modulation(conf);
    auto trg = cut(src, conf);

    auto src_n = apply_white_noise(src, conf["source"]);
    auto trg_n = apply_white_noise(trg, conf["target"]);

    auto keys = generate_modulation_keys(conf);

    GnuplotParams plot;

    plot.title = "source";
    plot.lines = {
        {"source", merge(keys, src)}};
    draw_plot(plot);

    plot.title = "target";
    plot.lines = {
        {"target", merge(keys, trg)}};
    draw_plot(plot);

    plot.title = "noised source";
    plot.lines = {
        {"source", merge(keys, src)},
        {"src_n", merge(keys, src_n)}};
    draw_plot(plot);

    plot.title = "noised target";
    plot.lines = {
        {"target", merge(keys, trg)},
        {"trg_n", merge(keys, trg_n)}};
    draw_plot(plot);
}