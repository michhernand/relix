#include <catch2/catch_test_macros.hpp>
#include <armadillo>
#include "algos.h"
#include "fixtures/mtcars.h"

TEST_CASE("Test Combinations-1") {
	arma::uvec input = {1, 2};

	arma::uword expected1 = 1;
	bool expected1_encountered = false;
	arma::uword expected2 = 2;
	bool expected2_encountered = false;
	arma::uword expected3 = 3;
	bool expected3_encountered = false;

	std::vector<arma::uvec> combos = generate_combinations(input);
	REQUIRE(combos.size() == 3);

	for (arma::uvec combo : combos) {
		arma::uword combo_sum = arma::accu(combo);
		if (combo_sum == expected1) {
			expected1_encountered = true;
		} else if (combo_sum == expected2) {
			expected2_encountered = true;
		} else if (combo_sum == expected3) {
			expected3_encountered = true;
		} else {
			WARN(combo_sum);
			REQUIRE(false);
		}
	}

	REQUIRE(
			(expected1_encountered &&
			expected2_encountered &&
			expected3_encountered)
	       );

}
