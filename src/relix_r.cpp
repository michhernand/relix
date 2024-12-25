#if defined(__LP64__) || defined(_WIN64) || defined(__x64_64__)
#define ARMA_64BIT_WORD
#endif

#include <string>
#include <vector>
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include "algos.h"
#include "relix.h"

// [[Rcpp::export]]
Rcpp::NumericVector relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y,
		std::string type,
		bool intercept
) {
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);

	std::unique_ptr<RelimpAlgorithm> ra; 

	if (type == "last") {
		ra = std::make_unique<LastRelimpAlgorithm>(intercept, std::vector<std::string>{});
	} else if (type == "first") {
		ra = std::make_unique<FirstRelimpAlgorithm>(intercept, std::vector<std::string>{});
	} else if (type == "lmg") {
		ra = std::make_unique<LMGRelimpAlgorithm>(intercept, std::vector<std::string>{});
	} else {
		Rcpp::Rcerr << "invlaid type argument";
		return Rcpp::NumericVector();
	}

	try {
		return Rcpp::wrap(relative_importance(x_arma, y_arma, *ra));
	} catch(const std::out_of_range& oor) {
		Rcpp::Rcerr << oor.what();
	} catch(const std::invalid_argument& ia) {
		Rcpp::Rcerr << ia.what();
	}
	return Rcpp::NumericVector();
}
