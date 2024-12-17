#include <armadillo>
#include <utility>
#include <vector>
#include "sort.h"
#include "algo_naive.h"
#include "column_contribution.h"

NaiveRelimpAlgorithm::NaiveRelimpAlgorithm() {}

arma::uword NaiveRelimpAlgorithm::n_iter(arma::dmat x) {
	return x.n_cols;
}

/**
*  @brief Naive RelimpAlgorithm for testing.
*  @param x The x matrix (independent variables) of the model.
*  @param y The y vector (dependent variable) of the model.
*  @param column_index The column being evaluated.
*  @return A ColumnContribution object tracking the column's importance.
*/
ColumnContribution NaiveRelimpAlgorithm::evaluate_column(
		arma::dmat x,
		arma::dvec y,
		arma::uword column_index
) {
	auto cc = ColumnContribution(column_index, column_index);
	return cc;
}

std::vector<ColumnContribution> NaiveRelimpAlgorithm::evaluate_columns(
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

std::pair<arma::uvec, arma::dvec> NaiveRelimpAlgorithm::sort_columns(
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
