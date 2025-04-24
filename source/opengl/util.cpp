#include "util.hpp"

#include <cstdlib>

#include <iostream>

namespace fractal {
void
fatal_error(std::string_view error)
{
    std::cerr << "Fatal error: " << error << "\n";
    std::exit(EXIT_FAILURE);
}
} // namespace fractal
