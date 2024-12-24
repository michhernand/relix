#include <armadillo>
#include <memory>
#include <stdexcept>
#include "algos.h"

std::unique_ptr<RelimpAlgorithm> get_algo(std::string& algo) {
	if (algo == "last") {
		return std::make_unique<LastRelimpAlgorithm>();
	}
	throw std::invalid_argument("invalid algo");
}


arma::dvec relative_importance(
		const arma::dmat& x, 
		const arma::dvec& y, 
		RelimpAlgorithm& algo
) {
	arma::dvec rsqs = algo.evaluate_columns(x, y);
	return rsqs;
}

arma::dvec relative_importance(
		const arma::dmat& x,
		const arma::dmat& y,
		std::string& algo
) {

	std::unique_ptr<RelimpAlgorithm> algoObj = get_algo(algo);
	auto ccs = algoObj->evaluate_columns(x, y);
	return ccs;
}
