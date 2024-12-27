#ifndef UTILS_H
#define UTILS_H

#include <armadillo>
#include <string>
#include <vector>

arma::uword lookup_index(std::string name, arma::field<std::string> headers);

arma::uvec select_except(const arma::dmat& x, arma::uword skip_col);

std::vector<std::string> get_headers(
		const arma::uvec ixs,
		const std::vector<std::string> headers
);

std::string get_headers_string(
		const arma::uvec ixs,
		const std::vector<std::string> headers
);

#endif

