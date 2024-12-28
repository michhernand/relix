#ifndef ALGOS_H
#define ALGOS_H

#include <armadillo>
#include <string>
#include <vector>

const std::string OOR_MSG = "tried to access an invalid column of x";

const std::string IA_MSG = "x has no columns";

std::vector<arma::uvec> generate_combinations(const arma::uvec& values);

arma::uvec select_except(const arma::dmat& x, arma::uword skip_col);

std::vector<std::string> get_headers(
		const arma::uvec ixs,
		const std::vector<std::string> headers
);

std::string get_headers_string(
		const arma::uvec ixs,
		const std::vector<std::string> headers
);

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
		);

		arma::dvec evaluate_columns(
				const arma::dmat& x, 
				const arma::dvec& y
		) override;
};

class FirstRelimpAlgorithm : public RelimpAlgorithm {
	private:
		bool intercept;
		std::vector<std::string> headers;
	public:
		FirstRelimpAlgorithm(
				bool intercept,
				std::vector<std::string> headers
		);

		arma::dvec evaluate_columns(
				const arma::dmat& x,
				const arma::dvec& y
		) override;
};

#endif
