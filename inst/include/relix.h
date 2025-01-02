#ifndef RELIX_H
#define RELIX_H

#ifndef ARMA_WARN_LEVEL
#define ARMA_WARN_LEVEL 1
#endif

#define ARMA_DONT_USE_WRAPPER
#define ARMA_DONT_PRINT_ERRORS

#include <armadillo>
#include <string>
#include <vector>
#include <boost/algorithm/string/join.hpp>

/**
* @brief Finds the index of a given column header.
* @param name The header to look up.
* @param headers All column headers.
* @return The index of the found header.
*/
inline arma::uword lookup_index(
		std::string name, 
		arma::field<std::string> headers
) {
	for (arma::uword i = 0; i < headers.size(); ++i) {
		std::string header = headers.at(i);
		if (header.front() == '"' && header.back() == '"') {
			header = header.substr(1, header.length() - 2);
		}
		if (header == name) {
			return i;
		}
	}
	return -1;
}

/**
* @brief Selects all column indexes of x except for i.
* @param x The matrix to select column indexes from.
* @param skip_col The column index to omit.
* @return A arma::uvec containing all column indexes except for i.
*/
inline arma::uvec select_except(const arma::dmat& x, arma::uword skip_col) {
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
inline std::vector<std::string> get_headers(const arma::uvec ixs, const std::vector<std::string> headers) {
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
inline std::string get_headers_string(const arma::uvec ixs, const std::vector<std::string> headers) {
	std::vector<std::string> chosen_headers = get_headers(ixs, headers);
	return boost::algorithm::join(chosen_headers, ", ");
}

inline arma::dmat add_intercept(const arma::dmat& x) {
	arma::vec intercept = arma::ones<arma::vec>(x.n_rows);
	return arma::join_horiz(x, intercept);

}

inline double basic_lm(const arma::dmat& x, const arma::dvec& y) {
    arma::vec beta = arma::solve(arma::trans(x) * x, arma::trans(x) * y);
    arma::vec y_pred = x * beta;
    arma::vec residuals = y - y_pred;

    double ss_res = arma::accu(arma::square(residuals));
    double ss_tot = arma::accu(arma::square(y - arma::mean(y)));
    
    double r_squared = 1 - (ss_res / ss_tot);
    return r_squared;
}

/**
* @brief Relative Importance algorithm to rank importance of linear model results.
*/
class RelimpAlgorithm {
	public:
		virtual ~RelimpAlgorithm() = default;

		/**
		* @brief Calculates rsq in excess of baseline for all cols.
		* @param x The independent variables of the regression.
		* @param y The dependent variable of the regression.
		* @return The excess r-squared for all cols.
		*/
		virtual arma::dvec evaluate_columns(
				const arma::dmat& x, 
				const arma::dvec& y
		) = 0;
};

class LastRelimpAlgorithm : public RelimpAlgorithm {
	private:
		bool intercept;
		std::vector<std::string> headers;
	public:
		LastRelimpAlgorithm(
				bool intercept,
				std::vector<std::string> headers
		) : intercept(intercept), headers(headers) {}

		/**
		* @brief Gathers r-squared values evaluating the importance of all x columns.
		* @param x The x matrix (independent variables) of the model.
		* @param y The y vector (dependent variable) of the model.
		* @return A vector of ColumnContribution objects (one per x column).
		*/
		arma::dvec evaluate_columns(
				const arma::dmat& x, 
				const arma::dvec& y
		) override {
		double baseline_rsq = basic_lm(x, y);

		arma::dvec rsqs = arma::zeros(x.n_cols);
		for (arma::uword i = 0; i < x.n_cols; ++i) {
			double rsq = basic_lm(x.cols(select_except(x, i)), y);
			rsqs[i] = baseline_rsq - rsq;
		}
		return rsqs;
	}
};

class FirstRelimpAlgorithm : public RelimpAlgorithm {
	private:
		bool intercept;
		std::vector<std::string> headers;
	public:
		FirstRelimpAlgorithm(
				bool intercept,
				std::vector<std::string> headers
		) : intercept(intercept), headers(headers) {};

		/**
		* @brief Gathers r-squared values evaluating the importance of all x columns.
		* @param x The x matrix (independent variables) of the model.
		* @param y The y vector (dependent variable) of the model.
		* @return A vector of ColumnContribution objects (one per x column).
		*/
		arma::dvec evaluate_columns(
				const arma::dmat& x,
				const arma::dvec& y
		) override {
			arma::dvec rsqs = arma::zeros(x.n_cols);
			for (arma::uword i = 0; i < x.n_cols; ++i) {
				if (this->intercept) {
					rsqs[i] = basic_lm(add_intercept(x.col(i)), y);
				} else {
					rsqs[i] = basic_lm(x.col(i), y);
				}
			}
			return rsqs;
		}
};

#endif

