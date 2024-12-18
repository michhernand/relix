#include <catch2/catch_test_macros.hpp>
#include <armadillo>
#include <memory>
#include "algo_naive.h"

TEST_CASE("Smoke Tests for NaiveRelimpAlgorithm") {
	arma::dmat x = arma::zeros(3, 4);
	arma::dvec y = arma::zeros(x.n_rows);
	
	std::unique_ptr<NaiveRelimpAlgorithm> ra(new NaiveRelimpAlgorithm);
	auto n_iter = ra->n_iter(x);
	REQUIRE(n_iter == x.n_cols);

	auto cc = ra->evaluate_column(x, y, 0);
	REQUIRE(cc.column == 0);
}
