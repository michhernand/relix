#include <armadillo>
#include <stdexcept>
#include <string>
#include <vector>
#include "lm.h"
#include "algos.h"


LMGRelimpAlgorithm::LMGRelimpAlgorithm(
		bool intercept,
		std::vector<std::string> headers
) : intercept(intercept), headers(headers) {}

double LMGRelimpAlgorithm::evaluate_column(
		const arma::dmat& x,
		const arma::dvec& y,
		const arma::uword i
) {
	arma::dvec toggle_col = x.col(i);
	std::vector<arma::uvec> combinations = generate_combinations(
			select_except(x, i)
	);


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

