#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#if defined(__LP64__) || defined(_WIN64) || defined(__x64_64__)
#define ARMA_64BIT_WORD
#endif

#include <string>
#include <vector>
#include "algos.h"
#include <iostream>

// [[Rcpp::export]]
Rcpp::NumericVector relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y,
		std::string type
) {
	bool intercept { true };
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);
	std::cout << "X ARMA SIZE: " << x_arma.n_elem;
	std::cout << "Y ARMA SIZE: " << y_arma.n_elem;
	std::vector<std::string> headers;

	std::unique_ptr<RelimpAlgorithm> ra; 

	if (type == "last") {
		ra = std::make_unique<LastRelimpAlgorithm>(intercept, headers);
	} else if (type == "first") {
		ra = std::make_unique<FirstRelimpAlgorithm>(intercept, headers);
	} else {
		Rcpp::stop("invlaid type argument");
	}

	try {
		return Rcpp::wrap(ra->evaluate_columns(x_arma, y_arma));
	} catch(const std::invalid_argument& ia) {
		Rcpp::stop(ia.what());
	} catch(const std::runtime_error& e) {
		Rcpp::stop("Error in linear model calculation: %s", e.what());
	} catch(const std::exception& e) {
		Rcpp::stop("Unexpected error: %s", e.what());
	}
	return Rcpp::NumericVector();
}
