#include <boost/algorithm/string/join.hpp>
#include <armadillo>
#include <string>
#include <vector>

/**
 * @brief Generate all possible combinations of all sizes from elements in values
 * @param values Vector of values to generate combinations from
 * @return Vector of uvec, each containing one combination of the input values
 */
std::vector<arma::uvec> generate_combinations(const arma::uvec& values) {
	std::vector<arma::uvec> combinations;

	// For each possible size k from 0 to n
	for (arma::uword k = 1; k <= values.n_elem; ++k) {
		std::vector<bool> v(values.n_elem);
		std::fill(v.begin(), v.begin() + k, true);

		do {
			arma::uvec combination(k);
			size_t idx = 0;
			for (size_t i = 0; i < values.n_elem; ++i) {
				if (v[i]) {
					combination[idx++] = values(i);
				}
			}
			
			combinations.push_back(combination);
		} while (std::prev_permutation(v.begin(), v.end()));
	}

	return combinations;
}

/**
* @brief Selects all column indexes of x except for i.
* @param x The matrix to select column indexes from.
* @param skip_col The column index to omit.
* @return A arma::uvec containing all column indexes except for i.
*/
arma::uvec select_except(const arma::dmat& x, arma::uword skip_col) {
	bool seen = false;
	arma::uvec selected = arma::zeros<arma::uvec>(x.n_cols - 1);

	for (arma::uword j = 0; j < x.n_cols; ++j) {
		if (j == skip_col) {
			seen = true;
			continue;
		}

		if (seen) {
			selected[j - 1] = j;
		} else {
			selected[j] = j;
		}
	}

	return selected;
}

/**
* @brief Gets selected headers from a vector of header strings.
* @param ixs A vector of headers to pick.
* @param headers A vector of headers to pick from.
* @return A std::vector<std::string> of chosen headers.
*/
std::vector<std::string> get_headers(const arma::uvec ixs, const std::vector<std::string> headers) {
	std::vector<std::string> output;
	for (arma::uword i = 0; i < ixs.size(); ++i) {
		if (i >= headers.size()) {
			throw std::out_of_range("tried to get out of range header");
		}
		output.push_back(headers[i]);
	}
	return output;
}

/**
* @brief Gets selected headers from a vector of header strings.
* @param ixs A vector of headers to pick.
* @param headers A vector of headers to pick from.
* @return A std::string of comma-delimited chosen headers.
*/
std::string get_headers_string(const arma::uvec ixs, const std::vector<std::string> headers) {
	std::vector<std::string> chosen_headers = get_headers(ixs, headers);
	return boost::algorithm::join(chosen_headers, ", ");
}
