#include "lib.hpp"

#include <exception>
#include <iostream>

int
main()
{
    try {
        fractal::run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal exception thrown: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
