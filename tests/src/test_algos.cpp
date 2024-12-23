#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <memory>
#include "algos.h"
#include "cc.h"

// TEST_CASE("Test LastRelimpAlgorithm.evaluate_column") {
// 	arma::dmat data = arma::zeros(5, 4);
// 	data.load("../tests/data/sample1.csv");
//
// 	REQUIRE(arma::accu(data) > 0);
//
// 	arma::dmat x = data.cols(0, 1);
// 	arma::dvec y = data.col(2);
//
// 	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);
//
// 	auto cc = ra->evaluate_column(x, y, 0);
//
// 	auto mean_without = cc.get_mean_without_column();
// 	REQUIRE_THAT(
// 			mean_without,
// 			Catch::Matchers::WithinRel(-2.985, 0.001)
// 	);
//
// 	auto mean_with = cc.get_mean_with_column();
// 	REQUIRE_THAT(
// 			mean_with, 
// 			Catch::Matchers::WithinRel(0.5265, 0.001)
// 	);
//
// 	auto lift = cc.get_lift();
// 	auto calculated_lift = mean_with - mean_without;
// 	REQUIRE_THAT(
// 			lift, 
// 			Catch::Matchers::WithinRel(calculated_lift, 0.001)
// 	);
// }

TEST_CASE("Test LastRelimpAlgorithm.evaluate_columns") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);

	auto ccs = ra->evaluate_columns(x, y);
	REQUIRE(ccs.size() == x.n_cols);

	for (ColumnContribution cc : ccs) {
		REQUIRE(cc.get_lift() != 0);
	}
}

