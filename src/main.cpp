#include <iostream>

#include "config/config.h"
#include "scenario/generation.h"

using std::cout;
using std::endl;

int main()
{
    try
    {
        auto conf = load_config("config.json");
        cout << "Config: " << conf << endl;

        generation(conf);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}