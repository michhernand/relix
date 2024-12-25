#include <armadillo>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "lm.h"
#include "algos.h"


LMGRelimpAlgorithm::LMGRelimpAlgorithm(
		const bool intercept,
		std::vector<std::string> headers 
) {
	this->intercept = intercept;
	this->headers = headers;
}

/**
 * @brief Generate all possible combinations of all sizes from elements in values
 * @param values Vector of values to generate combinations from
 * @return Vector of uvec, each containing one combination of the input values
 */
std::vector<arma::uvec> generate_combinations(const arma::uvec& values) {
	std::vector<arma::uvec> combinations;

	// For each possible size k from 0 to n
	for (arma::uword k = 0; k <= values.n_elem; ++k) {
		std::vector<bool> v(values.n_elem);
		std::fill(v.begin(), v.begin() + k, true);

		do {
			arma::uvec combination(k);
			size_t idx = 0;
			for (size_t i = 0; i < values.n_elem; ++i) {
				if (v[i]) {
					combination[idx++] = values(i);
				}
			}
			combinations.push_back(combination);
		} while (std::prev_permutation(v.begin(), v.end()));
	}

	return combinations;
}

double LMGRelimpAlgorithm::evaluate_column(
		const arma::dmat& x,
		const arma::dvec& y,
		const arma::uword i
) {
	arma::dvec toggle_col = x.col(i);
	std::vector<arma::uvec> combinations = generate_combinations(
			select_except(x, i)
	);

	// std::cout << "Combos: " << combinations << std::endl;
	std::cout << "COMBOS" << std::endl;
	for (size_t j = 0; j < combinations.size(); ++j) {
		std::cout << " " << j << ": " << combinations[j].t() << std::endl;
	}
	std::cout << "END" << std::endl;

	double lmw;
	double lmwo;
	arma::dvec rsqs = arma::zeros(combinations.size());
	for (arma::uword j = 0; j < combinations.size(); ++j) {
		if (this->intercept) {
			lmwo = basic_lm(
				add_intercept(
					x.cols(combinations[i])
				), y
			);

			lmw = basic_lm(
				add_intercept(
					arma::join_horiz(
						x.cols(combinations[i]), 
						toggle_col
					)
				), y
			);
		} else {
			lmwo = basic_lm(
				x.cols(combinations[i]), y
			);

			lmw = basic_lm(
				arma::join_horiz(
					x.cols(combinations[i]), 
					toggle_col
				), y
			);
		}
		rsqs[j] = lmw - lmwo;
	}

	return arma::mean(rsqs);
}

arma::dvec LMGRelimpAlgorithm::evaluate_columns(
		const arma::dmat& x,
		const arma::dvec& y
) {
	if (x.n_cols == 0) {
		throw std::invalid_argument(IA_MSG);
	}

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		rsqs[i] = this->evaluate_column(x, y, i);
	}
	return rsqs;
}
