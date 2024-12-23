#ifndef ALGOS_H
#define ALGOS_H

#include <armadillo>
#include "cc.h"
#include "lm.h"

/**
* @brief Relative Importance algorithm to rank importance of linear model results.
*/
class RelimpAlgorithm {
	public:
		virtual ~RelimpAlgorithm() = default;
		virtual ColumnContribution evaluate_column(
				arma::dmat x, 
				arma::dvec y, 
				arma::uword column_index,
				Model full_model
		) = 0;

		virtual std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x, 
				arma::dvec y
		) = 0;
};

class LastRelimpAlgorithm : public RelimpAlgorithm {
	public:
		LastRelimpAlgorithm();
		ColumnContribution evaluate_column(
				arma::dmat x, 
				arma::dvec y, 
				arma::uword column_index,
				Model full_model
		) override;

		std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x, 
				arma::dvec y
		) override;
};

class FirstRelimpAlgorithm : public RelimpAlgorithm {
	private:
		double get_sum_rsquared(
				arma::dmat x,
				arma::dvec y
		);
	public:
		FirstRelimpAlgorithm();
		ColumnContribution evaluate_column(
				arma::dmat x,
				arma::dvec y,
				arma::uword column_index,
				Model full_model
		) override;

		std::vector<ColumnContribution> evaluate_columns(
				arma::dmat x,
				arma::dvec y
		) override;
};

#endif
