#include <armadillo>
#include <stdexcept>
#include "lm.h"
#include "algos.h"



const std::string ERR_MSG = "tried to access an invalid column of x";


/**
* @brief Selects all columns of x except for i.
* @param x The matrix to select columns from.
* @param i The column to omit.
* @return A arma::dmat containing all columns except for i.
*/
arma::dmat select_except(const arma::dmat& x, arma::uword i) {
	const arma::uword n = x.n_cols - 1;
	arma::uvec cols = arma::regspace<arma::uvec>(0, n);
	cols.shed_row(i);
	return x.cols(cols);
}

LastRelimpAlgorithm::LastRelimpAlgorithm() {}


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
	if (x.n_cols == 0) {
		throw std::runtime_error("x has no columns");
	}

	double baseline_rsq = basic_lm(x, y);

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		if (i >= x.n_cols) {
			throw std::runtime_error(ERR_MSG);
		}
		rsqs[i] = baseline_rsq - basic_lm(select_except(x, i), y);
	}
	return rsqs;
}

FirstRelimpAlgorithm::FirstRelimpAlgorithm(const bool intercept) {
	this->intercept = intercept;
}

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
		throw std::runtime_error("x has no columns");
	}

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		if (i >= x.n_cols) {
			throw std::runtime_error(ERR_MSG);
		}
		if (this->intercept) {
			rsqs[i] = basic_lm(add_intercept(x.col(i)), y);
		} else {
			rsqs[i] = basic_lm(x.col(i), y);
		}
	}
	return rsqs;
}
