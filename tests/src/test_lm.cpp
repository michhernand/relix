#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <armadillo>
#include <memory>
#include <utility>
#include "cc.h"
#include "lm.h"
#include "fixtures/mtcars.h"


TEST_CASE_METHOD(MTCars, "Test Comparison with R - lm") {
	Model result = basic_lm(get_x(), get_y());
	REQUIRE_THAT(
			result.r_squared,
			Catch::Matchers::WithinRel(0.869, 0.001)
	);
} 


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

