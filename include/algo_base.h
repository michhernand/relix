#ifndef RELIMP_ALGORITHM_H
#define RELIMP_ALGORITHM_H

#include <armadillo>
#include <utility>
#include "column_contribution.h"

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

#endif
