#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include "lm.h"
#include "fixtures/mtcars.h"


TEST_CASE_METHOD(MTCars, "Test Comparison with R - lm1") {
	Model result = basic_lm(get_x(), get_y());
	REQUIRE_THAT(
			result.r_squared,
			Catch::Matchers::WithinRel(0.869, 0.001)
	);
} 

TEST_CASE_METHOD(MTCars, "Test Comparison with R - lm2") {
	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};
	Model result = basic_lm(get_x(x_labs), get_y());
	REQUIRE_THAT(
			result.r_squared,
			Catch::Matchers::WithinRel(0.782, 0.001)
	);
}

TEST_CASE_METHOD(MTCars, "Test Comparison with R - lm3") {
	std::vector<std::string> x_labs = {"qsec", "vs", "am", "gear"};
	Model result = basic_lm(get_x(x_labs), get_y());
	REQUIRE_THAT(
			result.r_squared,
			Catch::Matchers::WithinRel(0.7197, 0.001)
	);
}

