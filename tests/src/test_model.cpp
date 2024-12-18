#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <memory>
#include "column_contribution.h"
#include "model.h"

TEST_CASE("Test Linear Model (100% RSQ)") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);

	Model result = basic_lm(x, y);
	REQUIRE_THAT(
			result.r_squared, 
			Catch::Matchers::WithinRel(0.7136, 0.001)
	);
}

TEST_CASE("Test Linear Model (50% RSQ)") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample2.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);

	Model result = basic_lm(x, y);
	REQUIRE_THAT(
			result.r_squared, 
			Catch::Matchers::WithinRel(0.4404, 0.001)
	);
}

TEST_CASE("Test Dual Linear Model") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);
	arma::dvec toggle = data.col(3);

	auto result = dual_lm(toggle, x, y);
	REQUIRE_THAT(
			result.first.r_squared,
			Catch::Matchers::WithinRel(0.9984, 0.001)
	);

	REQUIRE_THAT(
			result.second.r_squared,
			Catch::Matchers::WithinRel(0.7136, 0.001)
	);
}

TEST_CASE("Test Dual Linear Model CC") {
	arma::dmat data = arma::zeros(5, 4);
	data.load("../tests/data/sample1.csv");

	REQUIRE(arma::accu(data) > 0);

	arma::dmat x = data.cols(0, 1);
	arma::dvec y = data.col(2);
	arma::dvec toggle = data.col(3);

	std::unique_ptr<ColumnContribution> cc(new ColumnContribution(0,1));
	dual_lm_cc(toggle, x, y, *cc);

	auto without_col = cc->get_mean_without_column();
	REQUIRE(without_col > 0);

	auto with_col = cc->get_mean_with_column();
	REQUIRE(with_col > 0);

	auto lift = cc->get_lift();
	REQUIRE(lift > 0);

	REQUIRE_THAT(
			lift,
			Catch::Matchers::WithinRel(
				with_col - without_col,
				0.01
			)
	);
}
