#include <catch2/catch_test_macros.hpp>
#include <armadillo>
#include <memory>
#include "algo_last.h"

TEST_CASE("Smoke Tests for LastRelimpAlgorithm") {
	arma::dmat x = arma::zeros(3, 4);
	arma::dvec y = arma::zeros(x.n_rows);

	std::unique_ptr<LastRelimpAlgorithm> ra(new LastRelimpAlgorithm);
	auto n_iter = ra->n_iter(x);
	REQUIRE(n_iter == x.n_cols);
}
