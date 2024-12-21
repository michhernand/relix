#ifndef ALGOS_H
#define ALGOS_H

#include <armadillo>
#include <utility>
#include "cc.h"

/**
* @brief Relative Importance algorithm to rank importance of linear model results.
*/
class RelimpAlgorithm {
	public:
		virtual ~RelimpAlgorithm() = default;
		virtual arma::uword n_iter(arma::dmat x) = 0;
		virtual ColumnContribution evaluate_column(
				arma::dmat x, 
				arma::dvec y, 
				arma::uword column_index
		) = 0;

		virtual std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x, 
				arma::dvec y
		) = 0;

		virtual std::pair<arma::uvec, arma::dvec> sort_columns(
				arma::dmat x, 
				arma::dvec y
		) = 0;
};

class NaiveRelimpAlgorithm : public RelimpAlgorithm {
	public:
		NaiveRelimpAlgorithm();
		arma::uword n_iter(arma::dmat x) override;
		std::vector<arma::uvec> permutations(
				arma::uword n_columns,
				arma::uword skip_index
		);
		ColumnContribution evaluate_column(
				arma::dmat x, 
				arma::dvec y, 
				arma::uword column_index
		) override;

		std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x, 
				arma::dvec y
		) override;

		std::pair<arma::uvec, arma::dvec> sort_columns(
				arma::dmat x, 
				arma::dvec y
		) override;
};

class LastRelimpAlgorithm : public RelimpAlgorithm {
	public:
		LastRelimpAlgorithm();
		arma::uword n_iter(arma::dmat x) override;
		arma::uvec permutations(
				arma::uword n_columns,
				arma::uword skip_index
		);
		ColumnContribution evaluate_column(
				arma::dmat x, 
				arma::dvec y, 
				arma::uword column_index
		) override;

		std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x, 
				arma::dvec y
		) override;

		std::pair<arma::uvec, arma::dvec> sort_columns(
				arma::dmat x, 
				arma::dvec y
		) override;
};

#endif
