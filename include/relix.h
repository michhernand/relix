#include <armadillo>
#include <memory>
#include "column_contribution.h"
#include "algo_base.h"

std::unique_ptr<RelimpAlgorithm> get_algo(std::string& algo);

std::vector<ColumnContribution> relative_importance(
		arma::dmat& x, 
		arma::dvec& y, 
		RelimpAlgorithm& algo
);

std::vector<ColumnContribution> relative_importance(
		arma::dmat& x,
		arma::dmat& y,
		std::string& algo
);
