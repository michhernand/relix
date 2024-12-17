#ifndef NAIVE_RELIMP_ALGORITHM_H
#define NAIVE_RELIMP_ALGORITHM_H

#include <armadillo>
#include <utility>
#include "algo_base.h"
#include "column_contribution.h"

class NaiveRelimpAlgorithm : public RelimpAlgorithm {
	public:
		NaiveRelimpAlgorithm();
		arma::uword n_iter(arma::dmat x) override;
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
