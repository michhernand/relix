#include <armadillo>
#include <stdexcept>
#include "lm.h"
#include "algos.h"



const std::string OOR_MSG = "tried to access an invalid column of x";

const std::string IA_MSG = "x has no columns";

/**
* @brief Selects all column indexes of x except for i.
* @param x The matrix to select columns from.
* @param skip_col The column to omit.
* @return A arma::uvec containing all column indexes except for i.
*/
arma::uvec select_except_ix(const arma::dmat& x, arma::uword skip_col) {
	bool seen = false;
	arma::uvec selected = arma::zeros<arma::uvec>(x.n_cols - 1);

	for (arma::uword j = 0; j < x.n_cols; ++j) {
		if (j == skip_col) {
			seen = true;
			continue;
		}

		if (seen) {
			selected[j - 1] = j;
		} else {
			selected[j] = j;
		}
	}

	return selected;
}

/**
* @brief Selects all columns of x except for i.
* @param x The matrix to select columns from.
* @param skip_col The column to omit.
* @return A arma::dmat containing all columns except for i.
*/
arma::dmat select_except(const arma::dmat& x, arma::uword skip_col) {
	return x.cols(select_except_ix(x, skip_col));
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
		throw std::invalid_argument(IA_MSG);
	}

	double baseline_rsq = basic_lm(x, y);

	arma::dvec rsqs = arma::zeros(x.n_cols);
	for (arma::uword i = 0; i < x.n_cols; ++i) {
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

LMGRelimpAlgorithm::LMGRelimpAlgorithm(const bool intercept) {
	this->intercept = intercept;
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
	std::vector<arma::uvec> combinations = generate_combinations(select_except_ix(x, i));

	double lmw;
	double lmwo;
	arma::dvec rsqs = arma::zeros(combinations.size());
	for (arma::uword j = 0; j < combinations.size(); ++j) {
		if (this->intercept) {
			lmwo = basic_lm(add_intercept(x.cols(combinations[i])), y);
			lmw = basic_lm(add_intercept(arma::join_horiz(x.cols(combinations[i]), toggle_col)), y);
		} else {
			lmwo = basic_lm(x.cols(combinations[i]), y);
			lmw = basic_lm(arma::join_horiz(x.cols(combinations[i]), toggle_col), y);
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
