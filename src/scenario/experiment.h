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
    const size_t &bits_len,
    const std::string &mod,
    const Ask2Params &mp,
    const CuttingParams &cp,
    const double &noise_source,
    const double &noise_target)
{
    std::string bits = random_bits(gen, bits_len);
    auto src = modulation_exp(mod, mp.Tb, mp.fs, mp.fc, mp.A0, mp.A1, bits);
    auto trg = cut(src, mp.Tb, mp.fs, bits_len, cp.begin, cp.end);

    apply_white_noise_raw(src, noise_source);
    apply_white_noise_raw(trg, noise_target);

    auto corr = correlation(src, trg);
    auto corr_abs = abs(corr);

#ifdef LOG
    std::cerr << "bits: " << bits << std::endl;
#endif

    return correlation_key(1. / mp.fs, cp.begin - cp.end, max_id(corr_abs));
}

void serial_experiment(
    std::mt19937 &gen,
    const size_t &bits_len,
    const std::string &mod,
    const Ask2Params &mp,
    const CuttingParams &cp,
    const double &noise_source,
    const double &noise_target,
    const size_t &exp_num,
    double &serial_exp_result)
{
    size_t count = 0;
    for (size_t i = 0; i < exp_num; ++i)
    {
        double res = single_experiment(
            gen, bits_len, mod, mp, cp, noise_source, noise_target);
        double diff = fabs(res - cp.begin);

#ifdef LOG
        std::cerr
            << "res: " << res
            << ", begin: " << cp.begin
            << ", diff: " << diff << std::endl;
#endif
        if (diff < mp.Tb)
            ++count;
    }
    serial_exp_result = double(count) / double(exp_num);

#ifdef LOG
    std::cerr << "serial_exp_result: " << serial_exp_result << ", count: "
              << count << ", exp_num: " << exp_num << std::endl;
#endif
}

void experiment(const Config &conf)
{
    ExperimentParams exp_p = conf;
    SourceParams src_p = conf;

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
            std::cout << "\rCurrent progress: " << (100. * float(completed_thread_count) / float(exp_p.noise_levels))
                      << "% (" << completed_thread_count << " of " << exp_p.noise_levels << ")"
                      << ", active_threads: " << active_thread_count;
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
                    exp_p.bits_len,
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
        std::cout << "\rCurrent progress: " << (100. * float(completed_thread_count) / float(exp_p.noise_levels))
                  << "% (" << completed_thread_count << " of " << exp_p.noise_levels << ")"
                  << ", active_threads: " << active_thread_count;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    for (auto &item : free_list)
        item.join();

    std::cout << GREEN << "\nExperiment is done\n"
              << RESET;

    nprint_vector(exp_result);

    auto exp_result_l = nline(ranged_keys(exp_result.size(), exp_p.noise_min, exp_p.noise_max), exp_result);

    GnuplotLineParams p;
    p.title = "experiment result: " + src_p.mod;
    p.x_label = "noise, dB";
    p.y_label = "p";
    p.lines = {exp_result_l};
    draw_plot(p);
}