#include <armadillo>
#include <vector>


std::vector<arma::uvec> last_permutations(
		arma::uword n_columns, 
		arma::uword skip_index
) {
        std::vector<arma::uvec> permutations;

        for (arma::uword i = 1; i <= n_columns; ++i) {
                arma::uvec indices;

                for (arma::uword j = 0; j < i; ++j) {
                        if (j != skip_index) {
                                indices.insert_rows(
						indices.n_rows, 
						arma::uvec{ j }
				);
                        }
                }
                permutations.push_back(indices);
        }

        return permutations;
}

