#include <armadillo>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "lm.h"
#include "algos.h"


/**
* @brief Produces the indices of the sorted vec.
* @param arr The arma::vec to sort.
* @param desc Sort in descending order.
* @return A arma::uvec containing the sorted indices.
*/
arma::uvec argsort_array(const arma::dvec& arr, bool desc) {
    arma::uvec indices = arma::regspace<arma::uvec>(0, arr.n_elem - 1);
    std::sort(
		    indices.begin(), 
		    indices.end(), 
		    [&arr, desc](arma::uword a, arma::uword b) {
      if (desc) {
        return arr[a] > arr[b];
      } 
        return arr[a] < arr[b];
    });
    return indices;
}

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
* @brief Gathers r-squared values to eval the importance of a value of x.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @param i The column being evaluated.
* @param baseline_rsq The baseline r-squared for comparison.
* @return The excess r-squared of the baseline.
*/
double LastRelimpAlgorithm::evaluate_column(
		const arma::dmat& x,
		const arma::dvec& y,
		const arma::uword i,
		const double baseline_rsq
) {
	if (i >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}
	return baseline_rsq - basic_lm(select_except(x, i), y);
}

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
		rsqs[i] = this->evaluate_column(x, y, i, baseline_rsq);
	}
	return rsqs;
}

FirstRelimpAlgorithm::FirstRelimpAlgorithm(const bool intercept) {
	this->intercept = intercept;
}


/**
* @brief Gathers r-squared values to eval the importance of a value of x.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @param i The column being evaluated.
* @return The excess r-squared of the baseline.
*/
double FirstRelimpAlgorithm::evaluate_column(
		const arma::dmat& x,
		const arma::dvec& y,
		const arma::uword i
) {
	if (i >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}

	if (this->intercept) {
		return basic_lm(add_intercept(x.col(i)), y);
	} else {
		return basic_lm(x.col(i), y);
	}
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
		rsqs[i] = this->evaluate_column(x, y, i);
	}
	return rsqs;
}
