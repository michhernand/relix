#define ARMA_64BIT_WORD
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include <string>
#include <vector>
#include <memory>
#include "algos.h"

// [[Rcpp::export]]
Rcpp::NumericVector relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y,
		std::string type
) {
	bool intercept { true };
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);
	std::vector<std::string> headers;

	std::unique_ptr<RelimpAlgorithm> ra; 

	if (type == "last") {
		ra = std::make_unique<LastRelimpAlgorithm>(true, std::vector<std::string>{});
	} else if (type == "first") {
		ra = std::make_unique<FirstRelimpAlgorithm>(true, std::vector<std::string>{});
	} else {
		Rcpp::stop("invlaid type argument");
		return Rcpp::NumericVector();

	}

	return Rcpp::wrap(ra->evaluate_columns(x_arma, y_arma));
}
