#include <armadillo>
#include <stdexcept>
#include <string>
#include <vector>
#include "lm.h"
#include "algos.h"

FirstRelimpAlgorithm::FirstRelimpAlgorithm(
		bool intercept,
		std::vector<std::string> headers 
) : intercept(intercept), headers(headers) {}

/**
* @brief Gathers r-squared values evaluating the importance of all x columns.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @return A vector of ColumnContribution objects (one per x column).
*/
arma::dvec FirstRelimpAlgorithm::evaluate_columns(
		const arma::dmat& x,
		const arma::dvec& y
) {
	if (x.n_cols == 0) {
		throw std::invalid_argument(IA_MSG);
	}

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		if (this->intercept) {
			rsqs[i] = basic_lm(add_intercept(x.col(i)), y);
		} else {
			rsqs[i] = basic_lm(x.col(i), y);
		}
	}
	return rsqs;
}
