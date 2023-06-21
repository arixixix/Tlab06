#include <iostream>

#include "formatter_ex.h"
#include "solver.h"

int main(int argc, char* argv[])
{
    float a = int(*argv[1]) - 48;
    float b = int(*argv[2]) - 48;
    float c = int(*argv[3]) - 48;

    std::cin >> a >> b >> c;

    float x1 = 0;
    float x2 = 0;

    try
    {
        solve(a, b, c, x1, x2);

        formatter(std::cout, "x1 = " + std::to_string(x1));
        formatter(std::cout, "x2 = " + std::to_string(x2));
    }
    catch (const std::logic_error& ex)
    {
        formatter(std::cout, ex.what());
    }

    return 0;
}
