#ifndef RELIX_H
#define RELIX_H

#include <armadillo>
#include <memory>
#include "algos.h"

std::unique_ptr<RelimpAlgorithm> get_algo(std::string& algo);

arma::dvec relative_importance(
		const arma::dmat& x, 
		const arma::dvec& y, 
		RelimpAlgorithm& algo
);

arma::dvec relative_importance(
		const arma::dmat& x,
		const arma::dmat& y,
		std::string& algo
);

#endif
