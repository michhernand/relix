#include <armadillo>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>
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

NaiveRelimpAlgorithm::NaiveRelimpAlgorithm() {}

arma::uword NaiveRelimpAlgorithm::n_iter(arma::dmat x) {
	return x.n_cols;
}

std::vector<arma::uvec> NaiveRelimpAlgorithm::permutations(
		arma::uword n_columns, 
		arma::uword skip_index
) {
        std::vector<arma::uvec> permutations;

        for (arma::uword i = 1; i <= n_columns; ++i) {
                arma::uvec indices;

                for (arma::uword j = 0; j < i; ++j) {
                        if (j != skip_index) {
                                indices.insert_rows(
						indices.n_rows, 
						arma::uvec{ j }
				);
                        }
                }
                permutations.push_back(indices);
        }

        return permutations;
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
	if (column_index >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}

	// Get all permutations of indexes of columns to get.
	auto permutations = this->permutations(x.n_cols, column_index);

	auto cc = ColumnContribution(column_index, permutations.size());
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

LastRelimpAlgorithm::LastRelimpAlgorithm() {}

arma::uword LastRelimpAlgorithm::n_iter(arma::dmat x) {
	return x.n_cols;
}

arma::uvec LastRelimpAlgorithm::permutations(
		arma::uword n_columns, 
		arma::uword skip_index
		) {
	arma::uvec permutations;

	arma::uvec n_columns_v = arma::regspace<arma::uvec>(0, n_columns-1);
	arma::uvec mask = (n_columns_v != skip_index);
	return n_columns_v.elem(arma::find(mask));
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
	if (column_index >= x.n_cols) {
		throw std::runtime_error("tried to access an invalid column of x");
	}

	// Get all permutations of indexes of columns to get.
	arma::uvec permutations = this->permutations(x.n_cols, column_index);

	// A column contribution object (column_contribution.cpp.
	auto cc = ColumnContribution(column_index, permutations.size());

	arma::dvec toggle_col = x.col(column_index);
	x.shed_col(column_index);
	dual_lm_cc(
			toggle_col,
			x, y, cc
	);

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

	if (x.n_cols != ccs.size()) {
		throw std::runtime_error("x size != ccs size");
	}


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

