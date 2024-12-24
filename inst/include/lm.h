#ifndef LM_H
#define LM_H

#include <armadillo>

arma::dmat add_intercept(const arma::dmat& x);

double basic_lm(
                const arma::dmat& x, 
                const arma::dvec& y
                );

#endif //MODEL_H

