#include <armadillo>
#include "permutations.h"
#include "algo_last.h"
#include "model.h"
#include "sort.h"

LastRelimpAlgorithm::LastRelimpAlgorithm() {}

arma::uword LastRelimpAlgorithm::n_iter(arma::dmat x) {
	return x.n_cols;
}

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
		arma::uword column_index
) {

	// Get all permutations of indexes of columns to get.
	auto permutations = last_permutations(x.n_cols, column_index);

	// A column contribution object (column_contribution.cpp.
	auto cc = ColumnContribution(column_index, permutations.size());

	for (arma::uword i = 0; i < permutations.size(); ++i) {

		// Get the indexes of columns to get.
		auto perm_x_ix = permutations[i];

		// Get columns using the indexes.
		auto perm_x = x.cols(perm_x_ix);

		dual_lm_cc(
				x.col(column_index),
				perm_x,
				y, cc
		);
	}
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
	std::vector<ColumnContribution> ccs;
	ccs.resize(x.n_cols, ColumnContribution(0, 0));

	for (arma::uword i = 0; i < x.n_cols; ++i) {
		ccs[i] = evaluate_column(x, y, i);
	}
	return ccs;
}

/**
* @brief Gathers avg r-squared values to eval the importance of all x columns.
* @param x The x matrix (independent variables) of the model.
* @param y The y vector (dependent variable) of the model.
* @return A pair containing 
*	a) the column indexes sorted most important to least important
*	b) the average r-squared lift for those columns.
*/
std::pair<arma::uvec, arma::dvec> LastRelimpAlgorithm::sort_columns(
		arma::dmat x,
		arma::dvec y
) {
	auto result = evaluate_columns(x, y);

	arma::dvec result_avgs(result.size());
	for (arma::uword i = 0; i < result.size(); ++i) {
		result_avgs[i] = result[i].get_lift();
	}

	arma::uvec result_order = argsort_array(result_avgs, true);
	return std::make_pair(result_order, result_avgs(result_order));
}

