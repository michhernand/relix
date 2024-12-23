#ifndef LM_H
#define LM_H

#include <armadillo>
#include "cc.h"

struct Model {
        arma::dvec coefficients;
        arma::dvec fitted_values;
        arma::dvec residuals;
        double r_squared;

        Model(
                        const arma::dvec& coefficients,
                        const arma::dvec& fitted_values,
                        const arma::dvec& residuals,
                        const double r_squared
             ) : coefficients(coefficients), fitted_values(fitted_values), residuals(residuals), r_squared(r_squared) {};
};

arma::dmat add_intercept(const arma::dmat& x);

Model basic_lm(
                const arma::dmat& x, 
                const arma::dvec& y
                );

Model basic_lm_except(
		arma::dmat x,
		const arma::dvec& y,
		arma::uword column_index
);

#endif //MODEL_H

