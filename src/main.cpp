#include <iostream>

#include "config/config.h"
#include "scenario/scenario.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    try
    {
        std::cerr << "Running program: " << argv[0] << std::endl;

        auto conf = load_config("config.json");
        std::cerr << "Config: " << conf << endl;

        // correlation_fft_scenario(conf);
        experiment(conf);
        // single_exp_check(conf);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

/**
 * поправить названия
 * сделать графики сигнала и корреляции на одной картинке
 * сделать 3 графика на одной картинке для эксперимента
 * сделать вывод инфы на графики
 */