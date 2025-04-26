#include "lib.hpp"
#ifdef __EMSCRIPTEN__
#  include <emscripten.h>

void
start_loop()
{
    emscripten_set_main_loop(fractal::tick, 0, true);
}
#else
void
start_loop()
{
    fractal::run_forever();
}
#endif

#include <exception>
#include <iostream>

int
main()
{
    try {
        fractal::setup();
        start_loop();
    } catch (const std::exception& e) {
        std::cerr << "Fatal exception thrown: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
