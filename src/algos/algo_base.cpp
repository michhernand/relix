#include <armadillo>
#include <utility>
#include "column_contribution.h"


/**
* @brief Relative Importance algorithm to rank importance of linear model results.
*/
class RelimpAlgorithm {
	public:
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

