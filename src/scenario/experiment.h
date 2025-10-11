#pragma once

#include "scenario/params.h"
#include "modulation/modulation.h"
#include "signal/signal.h"
#include "general/general.h"
#include "noise/noise.h"
#include "signal/correlation.h"
#include <thread>
#include <list>

// #define LOG

double single_experiment(
    std::mt19937 &gen,
    const std::string &mod,
    const Ask2Params &mp,
    const CuttingParams &cp,
    const double &noise_source,
    const double &noise_target,
    const size_t &src_size,
    std::vector<cmplx> &src,
    std::vector<cmplx> &trg,
    std::vector<cmplx> &corr,
    std::vector<double> &corr_abs)
{
    std::string bits = random_bits(gen, mp.bits);
    apply_modulation_exp(mod, mp.Tb, mp.fs, mp.fc, mp.A0, mp.A1, bits, src);
    auto trg_size = apply_cut(src, trg, mp.Tb, mp.fs, mp.bits, cp.begin, cp.end);

    apply_white_noise_raw(src, noise_source, src_size);
    apply_white_noise_raw(trg, noise_target, trg_size);

    correlation_fft(src, trg, corr);
    apply_abs(corr, corr_abs);

#ifdef LOG
    std::cerr << "bits: " << bits << std::endl;
#endif

    return correlation_key(1. / mp.fs, 0, max_id(corr_abs));
}

void serial_experiment(
    std::mt19937 &gen,
    const std::string &mod,
    const Ask2Params &mp,
    const CuttingParams &cp,
    const double &noise_source,
    const double &noise_target,
    const size_t &exp_num,
    double &serial_exp_result)
{
    size_t src_size = mp.bits / mp.Tb * mp.fs;
    size_t corr_size = next_power_of_two(src_size);
    std::vector<cmplx> src(corr_size, cmplx{});
    std::vector<cmplx> trg(corr_size, cmplx{});
    std::vector<cmplx> corr(corr_size, cmplx{});
    std::vector<double> corr_abs(corr_size, double{});

    size_t count = 0;
    for (size_t i = 0; i < exp_num; ++i)
    {
        double res = single_experiment(
            gen, mod, mp, cp, noise_source, noise_target, src_size, src, trg, corr, corr_abs);
        double diff = fabs(res - cp.begin);

#ifdef LOG
        std::cerr
            << "res: " << res
            << ", begin: " << cp.begin
            << ", diff: " << diff << std::endl;
#endif
        if (diff < 1. / mp.Tb)
            ++count;
    }
    serial_exp_result = double(count) / double(exp_num);

#ifdef LOG
    std::cerr << "serial_exp_result: " << serial_exp_result << ", count: "
              << count << ", exp_num: " << exp_num << std::endl;
#endif
}

std::vector<double> experiment(const Config &conf)
{

    ExperimentParams exp_p = conf;
    SourceParams src_p = conf;

    std::cout << YELLOW << "Эксперимент начат для модуляции " << src_p.mod << RESET << std::endl;

    auto generators = create_random(exp_p.threads);

    double noise_step = (exp_p.noise_max - exp_p.noise_min) / double(exp_p.noise_levels - 1);
    std::vector<double> exp_result(exp_p.noise_levels);

    std::list<std::thread> free_list;
    size_t active_thread_count = 0;
    size_t thread_count = 0;
    size_t completed_thread_count = 0;

    for (size_t i = 0; i < exp_p.noise_levels; ++i)
    {
        while (active_thread_count == exp_p.threads)
        {
            std::cout << "\rТекущий прогресс: " << (100. * float(completed_thread_count) / float(exp_p.noise_levels))
                      << "% (" << completed_thread_count << " из " << exp_p.noise_levels << ")"
                      << ", активные потоки: " << active_thread_count << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        free_list.remove_if([](std::thread &trg)
                            { return !trg.joinable(); });

        double cur_noise = exp_p.noise_min + noise_step * i;
        ++active_thread_count;
        ++thread_count;
        free_list.emplace_back(std::thread(
            [&, cur_noise, i]
            {
                serial_experiment(
                    generators[thread_count % exp_p.threads],
                    src_p.mod,
                    conf,
                    conf,
                    src_p.noise,
                    cur_noise,
                    exp_p.experiments_per_level,
                    exp_result[i]);
                --active_thread_count;
                ++completed_thread_count;
            }));
    }

    while (active_thread_count > 0)
    {
        std::cout << "\rТекущий прогресс: " << (100. * float(completed_thread_count) / float(exp_p.noise_levels))
                  << "% (" << completed_thread_count << " из " << exp_p.noise_levels << ")"
                  << ", активные потоки: " << active_thread_count << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    for (auto &item : free_list)
        item.join();

    std::cout << YELLOW << "\nЭксперимент завершен для модуляции " << src_p.mod << RESET << std::endl;
    return exp_result;
}

void all_in_one_experiment(const Config &conf)
{
    Config new_conf = conf;

    new_conf["Опорный сигнал"]["Тип модуляции"] = "bpsk";
    auto bpsk_res = experiment(new_conf);

    new_conf["Опорный сигнал"]["Тип модуляции"] = "bfsk";
    auto bfsk_res = experiment(new_conf);

    new_conf["Опорный сигнал"]["Тип модуляции"] = "ask2";
    auto ask2_res = experiment(new_conf);

    std::cout
        << GREEN << "\nЭксперимент завершен\n"
        << RESET;

    ExperimentParams exp_p = conf;
    auto keys = ranged_keys(exp_p.noise_levels, exp_p.noise_min, exp_p.noise_max);

    auto bpsk_l = line("bpsk", keys, bpsk_res);
    auto bfsk_l = line("bfsk", keys, bfsk_res);
    auto ask2_l = line("ask2", keys, ask2_res);

    GnuplotParams p;
    p.title = "Результат эксперимента для 3 типов модуляции";
    p.x_label = "Уровень шума, дБ";
    p.y_label = "Вероятность ошибки";
    p.lines = {bpsk_l, bfsk_l, ask2_l};
    draw_plot(p);
    show_pic(p.title);
}