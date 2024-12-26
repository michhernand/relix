#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

#if defined(__LP64__) || defined(_WIN64) || defined(__x64_64__)
#define ARMA_64BIT_WORD
#endif

#include <string>
#include <vector>
#include "algos.h"

// [[Rcpp::export]]
Rcpp::NumericVector relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y,
		std::string type,
		bool intercept
) {
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);
	std::vector<std::string> headers;

	std::unique_ptr<RelimpAlgorithm> ra; 

	if (type == "last") {
		ra = std::make_unique<LastRelimpAlgorithm>(intercept, headers);
	} else if (type == "first") {
		ra = std::make_unique<FirstRelimpAlgorithm>(intercept, headers);
	} else {
		Rcpp::Rcerr << "invlaid type argument";
		return Rcpp::NumericVector();
	}

	try {
		return Rcpp::wrap(ra->evaluate_columns(x_arma, y_arma));
	} catch(const std::invalid_argument& ia) {
		Rcpp::stop(ia.what());
	}
	return Rcpp::NumericVector();
}
