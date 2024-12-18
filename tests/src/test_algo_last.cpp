#include <catch2/catch_test_macros.hpp>
#include <armadillo>
#include <memory>
#include "algo_last.h"
#include "column_contribution.h"

TEST_CASE("Smoke Tests for LastRelimpAlgorithm") {
	arma::dmat x = arma::zeros(5, 4);
	arma::dvec y = arma::zeros(x.n_rows);

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);
	auto n_iter = ra->n_iter(x);
	REQUIRE(n_iter == x.n_cols);
}

TEST_CASE("Test LastRelimpAlgorithm.evaluate_column") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);

	auto cc = ra->evaluate_column(x, y, 0);
	WARN(cc.get_lift());
	WARN(cc.get_mean_with_column());
	WARN(cc.get_mean_without_column());
	REQUIRE(1==1);
}

TEST_CASE("Test LastRelimpAlgorithm.evaluate_columns") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);
	auto ccs = ra->evaluate_columns(x, y);
	REQUIRE(ccs.size() > 0);
	REQUIRE(ccs.size() == x.n_cols);
	
	for (ColumnContribution cc : ccs) {
		WARN(cc.get_lift());
	}
	REQUIRE(1==1);
}
