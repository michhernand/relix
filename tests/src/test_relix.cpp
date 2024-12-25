#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <string>
#include "relix.h"
#include "algos.h"
#include "fixtures/mtcars.h"

TEST_CASE_METHOD(MTCars, "Test-LastPipeline-1") {
	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};

	LastRelimpAlgorithm ra = LastRelimpAlgorithm(true, x_labs);
	arma::dvec rsqs = relative_importance(get_x(x_labs), get_y(), ra);

	std::vector<double> expected_vals = {
		0.007498782,
		0.0131126143,
		0.0174177949,
		0.0146241073
	};
	for (arma::uword i; i < expected_vals.size(); ++i) {
		if (i >= rsqs.size()) {
			throw std::runtime_error("tried to access an out-of-bounds value of rsqs");
		}
		REQUIRE_THAT(
			rsqs[i],
			Catch::Matchers::WithinRel(
				expected_vals[i],
				0.001
			)
		);
	}
}


TEST_CASE_METHOD(MTCars, "Test-FirstPipeline-1") {
	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};

	FirstRelimpAlgorithm ra = FirstRelimpAlgorithm(true, x_labs);
	arma::dvec rsqs = relative_importance(get_x(x_labs), get_y(), ra);

	std::vector<double> expected_vals = {
		0.7261800,
		0.7183433,
		0.6024373,
		0.4639952
	};
	for (arma::uword i; i < expected_vals.size(); ++i) {
		if (i >= rsqs.size()) {
			throw std::runtime_error("tried to access an out-of-bounds value of rsqs");
		}
		REQUIRE_THAT(
			rsqs[i],
			Catch::Matchers::WithinRel(
				expected_vals[i],
				0.001
			)
		);
	}
}
