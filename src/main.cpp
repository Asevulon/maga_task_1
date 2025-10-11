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

        std::string mod = conf["Режим работы"];
        if (mod == "оценка_задержки")
            correlation_fft_scenario(conf);
        else if (mod == "исследование_устойчивости")
            all_in_one_experiment(conf);
        else
            throw std::runtime_error(
                "Неизвестный режим работы"
                ", возможные режимы работы: " +
                conf["Возможные режимы работы"].dump());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << RED << "Обнаружена ошибка, детали в log/run.txt"
                  << RESET << std::endl;
    }

    return 0;
}

/**
 * поправить названия
 * сделать графики сигнала и корреляции на одной картинке
 * сделать 3 графика на одной картинке для эксперимента
 * сделать вывод инфы на графики
 */