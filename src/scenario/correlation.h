#pragma once

#include "modulation/modulation.h"
#include "signal/signal.h"
#include "noise/noise.h"
#include "signal/correlation.h"
#include "plot/plot_line.h"
#include "general/colors.h"

void correlation_fft_scenario(const Config &conf)
{
    auto src = modulation_cmplx(conf);
    auto trg = cut(src, conf);

    auto src_n = apply_white_noise(src, conf["Опорный сигнал"]);
    auto trg_n = apply_white_noise(trg, conf["Исследуемый сигнал"]);

    auto src_keys = generate_modulation_keys(conf);
    auto trg_keys = cut(src_keys, conf);

    auto src_f = src_n;
    auto trg_f = trg_n;
    size_t corr_size = next_power_of_two(src.size());
    std::vector<cmplx> corr(corr_size, cmplx());
    zero_extention(src_f, corr_size);
    zero_extention(trg_f, corr_size);
    correlation_fft(src_f, trg_f, corr);
    auto corr_abs = abs(corr);

    double corr_max = milliseconds(src_keys[max_id(corr_abs)]);
    double error_rate = milliseconds(1. / conf["Опорный сигнал"]["Битовая скорость, бит/с"].get<double>());
    double init_value = conf["Исследуемый сигнал"]["Начало, мс"];
    double diff = fabs(corr_max - init_value);
    bool success = diff < error_rate;

    std::cout
        << YELLOW
        << "Максимальная корреляция обнаружена в " << corr_max << "мс"
        << " с доверительным интервалом " << error_rate << "мс.\n"
        << "Заданное значение задержки " << init_value << "мс.\n"
        << RESET;

    if (success)
    {
        std::cout
            << GREEN
            << "Сигнал был успешно обнаружен с ошибкой " << diff << "мс.\n"
            << RESET;
    }
    else
    {
        std::cout
            << RED
            << "Значение ошибки слишком велико " << diff << "мс.\n"
            << RESET;
    }

    GnuplotParams p;
    p.x_label = "Время, с";
    p.y_label = "Уровень сигнала";

    auto src_l = line("Опорный сигнал", src_keys, src);
    auto trg_l = line("Исследуемый сигнал", trg_keys, trg);
    auto src_n_l = line("Опорный сигнал c шумом", src_keys, src_n);
    auto trg_n_l = line("Исследуемый сигнал c шумом", trg_keys, trg_n);
    auto corr_abs_l = line("Корреляция", src_keys, corr_abs);

    p.title = "Опорный сигнал";
    p.lines = {src_l};
    draw_plot(p);

    p.title = "Исследуемый сигнал";
    p.lines = {trg_l};
    draw_plot(p);

    p.title = "Опорный сигнал c шумом";
    p.lines = {src_n_l};
    draw_plot(p);

    p.title = "Исследуемый сигнал c шумом";
    p.lines = {trg_n_l};
    draw_plot(p);

    p.title = "Корреляция\nМаксимум найден в " + std::to_string(corr_max) + "мс";
    p.x_label = "Величина сдвига, с";
    p.y_label = "Величина корреляции";
    p.lines = {corr_abs_l};
    draw_plot(p);

    show_pic("Опорный сигнал c шумом");
    show_pic("Исследуемый сигнал c шумом");
    show_pic("Корреляция");
}