#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <armadillo>

TEST_CASE("Check that 1 == 1") {
    REQUIRE(1 == 1);
}

