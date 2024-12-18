#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <armadillo>

std::vector<arma::uvec> last_permutations(
		arma::uword n_columns, 
		arma::uword skip_index
);

#endif
