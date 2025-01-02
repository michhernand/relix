#include <armadillo>
#include <string>
#include <vector>
#include "lm.h"
#include "algos.h"
#include "utils.h"

LastRelimpAlgorithm::LastRelimpAlgorithm(
		bool intercept,
		std::vector<std::string> headers 
) : intercept(intercept), headers(headers) {}


/**
* @brief Gathers r-squared values evaluating the importance of all x columns.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @return A vector of ColumnContribution objects (one per x column).
*/
arma::dvec LastRelimpAlgorithm::evaluate_columns(
		const arma::dmat& x,
		const arma::dvec& y
) {
	double baseline_rsq = basic_lm(x, y);

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		double rsq = basic_lm(x.cols(select_except(x, i)), y);
		rsqs[i] = baseline_rsq - rsq;
	}
	return rsqs;
}

