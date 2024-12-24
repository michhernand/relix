#include <armadillo>
#include "algos.h"

arma::dvec relative_importance(
		const arma::dmat& x, 
		const arma::dvec& y, 
		RelimpAlgorithm& algo
) {
	arma::dvec rsqs = algo.evaluate_columns(x, y);
	return rsqs;
}

