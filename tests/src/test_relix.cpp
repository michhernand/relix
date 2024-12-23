#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <string>
#include "relix.h"
#include "algos.h"
#include "fixtures/mtcars.h"

TEST_CASE_METHOD(MTCars, "Test-Pipeline-1") {
	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};

	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
	std::vector<ColumnContribution> ccs = relative_importance(get_x(x_labs), get_y(), ra);

	std::vector<double> expected_vals = {
		0.0726,
		0.0074987,
		0.0131126,
		0.0174177, 
		0.0146241
	};
	for (arma::uword i; i < ccs.size(); ++i) {
		REQUIRE_THAT(
			ccs[i].get_lift(),
			Catch::Matchers::WithinRel(
				expected_vals[i],
				0.001
			)
		);
	}
}


TEST_CASE_METHOD(MTCars, "Test-Pipeline-2") {
	std::vector<std::string> x_labs = {"qsec", "vs", "am", "gear"};

	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
	std::vector<ColumnContribution> ccs = relative_importance(get_x(x_labs), get_y(), ra);

	std::vector<double> expected_vals = {
		0.00058800,
		0.02968600,
		0.03160428,
		0.14545843,
		0.00024795,
	};
	for (arma::uword i; i < ccs.size(); ++i) {
		REQUIRE_THAT(
			ccs[i].get_lift(),
			Catch::Matchers::WithinRel(
				expected_vals[i],
				0.001
			)
		);
	}
}
