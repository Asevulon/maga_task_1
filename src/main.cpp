#include <iostream>

#include "config/config.h"
#include "scenario/scenario.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    try
    {
        std::cout << YELLOW << "Running program: " << argv[0] << RESET << std::endl;

        auto conf = load_config("config.json");
        cout << "Config: " << conf << endl;

        experiment(conf);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}