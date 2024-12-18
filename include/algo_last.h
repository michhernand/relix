#ifndef LAST_RELIMP_ALGORITHM_H
#define LAST_RELIMP_ALGORITHM_H

#include <armadillo>
#include "algo_base.h"
#include "column_contribution.h"

class LastRelimpAlgorithm : public RelimpAlgorithm {
	public:
		LastRelimpAlgorithm();
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
