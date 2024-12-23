#include <armadillo>
#include <stdexcept>
#include "lm.h"

const std::string DEFAULT_PATH = "../tests/data/mtcars.csv";

const std::string DEFAULT_Y_LAB = "mpg";
const std::vector<std::string> DEFAULT_X_LABS = {
	"model", "cyl", "disp",
	"hp", "drat", "wt", "qsec", "vs",
	"am", "gear", "carb"
};

class MTCars {
	private:
		arma::dmat data;
		arma::field<std::string> headers;
		const std::string path;

		arma::uword lookup_index(
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

	public:
		MTCars(const std::string& path = DEFAULT_PATH)
			: path(path)
		{
			bool ok = this->data.load(
					arma::csv_name(
						this->path, 
						this->headers
					)
			);

			if (!ok) {
				throw std::runtime_error(
						"failed to load test data csv"
				);
			}
		}

	protected:
		arma::dvec get_y(std::string lab = DEFAULT_Y_LAB) {
			arma::uword y_ix = this->lookup_index(lab, headers);
			if (y_ix == -1) {
				throw std::runtime_error("failed to find y index");
			}
			return data.col(y_ix);
		}

		arma::dmat get_x(
				std::vector<std::string> labs = DEFAULT_X_LABS, 
				bool intercept = true
		) {
			arma::uvec x_ixs(labs.size());
			for (arma::uword i = 0; i < labs.size(); ++i) {
				arma::uword x_ix = this->lookup_index(labs[i], headers);
				if (x_ix == -1) {
					throw std::runtime_error("failed to find x index");
				}
				x_ixs[i] = x_ix;
			}

			if (intercept) {
				return add_intercept(data.cols(x_ixs));
			} else {
				return data.cols(x_ixs);
			}
		}
};
