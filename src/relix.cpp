#include <armadillo>
#include <memory>
#include <stdexcept>
#include "algos.h"
#include "cc.h"

std::unique_ptr<RelimpAlgorithm> get_algo(std::string& algo) {
	if (algo == "last") {
		return std::make_unique<LastRelimpAlgorithm>();
	}
	throw std::invalid_argument("invalid algo");
}


std::vector<ColumnContribution> relative_importance(
		const arma::dmat& x, 
		const arma::dvec& y, 
		RelimpAlgorithm& algo
) {
	std::vector<ColumnContribution> ccs = algo.evaluate_columns(x, y);
	sort_cc(ccs);
	return ccs;
}

std::vector<ColumnContribution> relative_importance(
		const arma::dmat& x,
		const arma::dmat& y,
		std::string& algo
) {
	std::unique_ptr<RelimpAlgorithm> algoObj = get_algo(algo);
	auto ccs = algoObj->evaluate_columns(x, y);

	sort_cc(ccs);
	return ccs;
}
