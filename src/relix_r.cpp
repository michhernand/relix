#if defined(__LP64__) || defined(_WIN64) || defined(__x64_64__)
#define ARMA_64BIT_WORD
#endif

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include "algos.h"
#include "relix.h"

// [[Rcpp::export]]
Rcpp::NumericVector relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y
) {
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);

	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
	return Rcpp::wrap(relative_importance(x_arma, y_arma, ra));
}
