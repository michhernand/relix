#include <armadillo>
#include "lm.h"

arma::dmat add_intercept(const arma::dmat& x) {
	arma::vec intercept = arma::ones<arma::vec>(x.n_rows);
	return arma::join_horiz(intercept, x);

}

Model basic_lm(
                const arma::dmat& x,
                const arma::dvec& y
              ) {
        arma::vec beta = arma::solve(x, y);
        arma::vec y_pred = x * beta;
        arma::vec residuals = y - y_pred;

        double ss_res = arma::accu(arma::square(residuals));
        double ss_tot = arma::accu(arma::square(y - arma::mean(y)));
        double r_squared = 1 - (ss_res / ss_tot);

        return Model(
                        beta, y_pred, residuals, r_squared
                    );
}
