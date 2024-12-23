#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include "relix.h"
#include "algos.h"
#include "fixtures/mtcars.h"

TEST_CASE_METHOD(MTCars, "Test-Pipeline-1") {
	std::vector<std::string> x_labs = {"cyl", "disp", "hp", "drat"};

	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
	std::vector<ColumnContribution> ccs = relative_importance(get_x(x_labs), get_y(), ra);

	for (ColumnContribution cc : ccs) {
		WARN(cc.get_lift());
	}
}

// TEST_CASE("Test Pipeline") {
// 	arma::dmat data = arma::zeros(5, 4);
// 	bool ok = data.load("../tests/data/sample1.csv");
//
// 	REQUIRE(ok);
// 	REQUIRE(arma::accu(data) > 0);
//
// 	arma::dmat x = data.cols(0, 1);
// 	arma::dvec y = data.col(2);
// 	
// 	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
// 	std::vector<ColumnContribution> ccs = relative_importance(x, y, ra);
//
// 	double last_lift = -9999;
// 	for (ColumnContribution cc : ccs) {
// 		REQUIRE(cc.get_lift() > last_lift);
// 		last_lift = cc.get_lift();
// 	}
// }
