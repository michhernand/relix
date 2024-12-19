#if defined(__LP64__) || defined(_WIN64) || defined(__x64_64__)
#define ARMA_64BIT_WORD
#endif

#include <vector>
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

#include "cc.h"
#include "algos.h"
#include "relix.h"

// [[Rcpp::export]]
Rcpp::List relix_r(
		Rcpp::NumericMatrix x,
		Rcpp::NumericVector y
) {
	arma::dmat x_arma = Rcpp::as<arma::dmat>(x);
	arma::dvec y_arma = Rcpp::as<arma::dvec>(y);

	LastRelimpAlgorithm ra = LastRelimpAlgorithm();
	std::vector<ColumnContribution> ccs = relative_importance(x_arma, y_arma, ra);

	// auto output = Rcpp::List::create();
	auto output_index = Rcpp::List::create();
	auto output_importance = Rcpp::List::create();
	for (ColumnContribution cc : ccs) {
		auto output_elem = Rcpp::List::create();

		output_index.push_back(cc.get_column());
		output_importance.push_back(cc.get_lift());
	}

	return Rcpp::List::create(
			Rcpp::Named("index") = Rcpp::wrap(output_index),
			Rcpp::Named("importance") = Rcpp::wrap(output_importance)
	);
}
