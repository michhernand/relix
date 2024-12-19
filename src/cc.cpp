#include <armadillo>
#include <algorithm>
#include "cc.h"

void sort_cc(std::vector<ColumnContribution>& ccs) {
	std::sort(ccs.begin(), ccs.end(), [](ColumnContribution& a, ColumnContribution& b) {
			return a.get_lift() < b.get_lift();
	});
}

void ColumnContribution::set_at_with_column(double val, arma::uword index) {
        this->r_squared_with_column[index] = val;
}

void ColumnContribution::set_at_without_column(double val, arma::uword index) {
        this->r_squared_without_column[index] = val;
}

/**
 * @brief ColumnContribution constructor.
 * @param column The index of the column being tracked..
 * @param n The number of permutations associated with this ColumnContribution. Used for pre-allocating vectors.
*/
ColumnContribution::ColumnContribution(
                arma::uword column,
                arma::uword n
                ) : 
        column(column),

	// Preallocate `r_squared_with_column` attribute with n-size zeros vector.
	// These are populated by RelimpAlgorithm. It loops over all permutations and updates these 1 by 1.
        r_squared_with_column(arma::dvec(n, arma::fill::zeros)),

	// Preallocate `r_squared_without_column` attribute with n-size zeros vector.
	// These are populated by RelimpAlgorithm. It loops over all permutations and updates these 1 by 1.
        r_squared_without_column(arma::dvec(n, arma::fill::zeros)),

        // Default i to 0.
        iteration(0) 

{}

arma::uword ColumnContribution::get_column() {
        return this->column;
}

void ColumnContribution::set_at(double with_val, double without_val, arma::uword index) {
        this->set_at_with_column(with_val, index);
        this->set_at_without_column(without_val, index);
}


void ColumnContribution::set_next(double with_val, double without_val) {
        if (this->iteration >= this->r_squared_without_column.size()) {
                throw std::runtime_error("column contribution out of range");
        }

        this->set_at_with_column(with_val, this->iteration);
        this->set_at_without_column(without_val, this->iteration);
        this->iteration++;
}

double ColumnContribution::get_mean_with_column() {
        return arma::mean(this->r_squared_with_column);
};

double ColumnContribution::get_mean_without_column() {
        return arma::mean(this->r_squared_without_column);
};

/**
 * @brief This provides the average added benefit (i.e. relative importance) of including this feature.
 * @return The net r-squared.
 */
double ColumnContribution::get_lift() {
        return this->get_mean_with_column() - this->get_mean_without_column();
}

