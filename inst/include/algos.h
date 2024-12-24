#ifndef ALGOS_H
#define ALGOS_H

#include <armadillo>

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
	public:
		LastRelimpAlgorithm();

		arma::dvec evaluate_columns(
				const arma::dmat& x, 
				const arma::dvec& y
		) override;
};

class FirstRelimpAlgorithm : public RelimpAlgorithm {
	private:
		bool intercept;
	public:
		FirstRelimpAlgorithm(const bool intercept);

		/**
		* @brief Calculates rsq in excess of baseline.
		* @param x The independent variables of the regression.
		* @param y The dependent variable of the regression.
		* @param i The index of the col to evaluate.
		* @param baseline_rsq The baseline r-squared to compare against.
		* @return The excess r-squared.
		*/
		double evaluate_column(
				const arma::dmat& x,
				const arma::dvec& y,
				const arma::uword i
		);

		arma::dvec evaluate_columns(
				const arma::dmat& x,
				const arma::dvec& y
		) override;
};

#endif
