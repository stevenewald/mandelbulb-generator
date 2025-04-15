#include "lib.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is mandelbulb-generator", "[library]")
{
    auto const lib = library{};
    REQUIRE(lib.name == "mandelbulb-generator");
}
