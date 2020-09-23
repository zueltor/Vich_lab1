#include <cstdlib>
#include <iostream>
#include "equation.h"

int main(int argc, char **argv) {
    Parameters cubic{};
    Roots r;
    std::cout.precision(4);
    if (argc < 6) {
        std::cout << "Expected 5 arguments: eps, delta, a, b, c\n";
        return EXIT_FAILURE;
    }
    cubic.eps = atof(argv[1]);
    cubic.delta = atof(argv[2]);
    cubic.a = atof(argv[3]);
    cubic.b = atof(argv[4]);
    cubic.c = atof(argv[5]);
    if (cubic.eps < 0) {
        std::cout << "Incorrect eps\n";
        return EXIT_FAILURE;
    }
    std::cout << "Solving x^3+(" << cubic.a << ")x^2+(" << cubic.b << ")x+(" << cubic.c << ")\n";
    solve(cubic,r);
    r.printAnwer();

    return EXIT_SUCCESS;
}
