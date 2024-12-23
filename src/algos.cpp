#include <armadillo>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "cc.h"
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

LastRelimpAlgorithm::LastRelimpAlgorithm() {}

/**
* @brief Gathers r-squared values to eval the importance of a value of x.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @param column_index The column being evaluated.
* @return A ColumnContribution object tracking the columns importance.
*/
ColumnContribution LastRelimpAlgorithm::evaluate_column(
		arma::dmat x,
		arma::dvec y,
		arma::uword column_index,
		Model full_model
) {
	if (column_index >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}

	x.shed_col(column_index);

	Model partial_model = basic_lm(x, y);

	auto cc = ColumnContribution(column_index, 1);
	cc.set_next(full_model.r_squared, partial_model.r_squared);

	return cc;
}

/**
* @brief Gathers r-squared values evaluating the importance of all x columns.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @return A vector of ColumnContribution objects (one per x column).
*/
std::vector<ColumnContribution> LastRelimpAlgorithm::evaluate_columns(
		arma::dmat x,
		arma::dvec y
) {
	if (x.n_cols == 0) {
		throw std::runtime_error("x has no columns");
	}

	std::vector<ColumnContribution> ccs;
	ccs.resize(x.n_cols, ColumnContribution(0, 0));

	Model full_model = basic_lm(x, y);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
		ccs[i] = evaluate_column(x, y, i, full_model);
	}
	return ccs;
}

FirstRelimpAlgorithm::FirstRelimpAlgorithm() {}

double FirstRelimpAlgorithm::get_sum_rsquared(arma::dmat x, arma::dvec y) {
	arma::dvec r_squared_values = arma::zeros(x.n_cols);
	for (arma::uword i; i < x.n_cols; ++i) {
		Model mod = basic_lm(x.col(i), y);
		r_squared_values[i] = mod.r_squared;
	}
	return arma::accu(r_squared_values);
}

ColumnContribution FirstRelimpAlgorithm::evaluate_column(
		arma::dmat x,
		arma::dvec y,
		arma::uword column_index,
		Model full_model
) {
	if (column_index >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}

	arma::uvec column_index_vec = {column_index};
	arma::dmat xx = add_intercept(x.cols(column_index_vec));

	Model partial_model = basic_lm(xx, y);

	auto cc = ColumnContribution(column_index, 1);;
	cc.set_next(partial_model.r_squared, 0);

	return cc;
}

std::vector<ColumnContribution> FirstRelimpAlgorithm::evaluate_columns(
		arma::dmat x,
		arma::dvec y
) {
	if (x.n_cols == 0) {
		throw std::runtime_error("x has no columns");
	}

	std::vector<ColumnContribution> ccs;
	ccs.resize(x.n_cols, ColumnContribution(0, 0));

	arma::dvec coefficients;
	arma::dvec fitted_values;
	arma::dvec residuals;

	Model full_model = Model(
			coefficients,
			fitted_values,
			residuals,
			get_sum_rsquared(x, y)
	);

	for (arma::uword i = 0; i < x.n_cols; ++i) {
		ccs[i] = this->evaluate_column(x, y, i, full_model);
	}
	return ccs;
}
