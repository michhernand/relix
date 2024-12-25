set -euo pipefail

Rscript -e "Rcpp::compileAttributes()"
R CMD build .
R CMD INSTALL --preclean --clean Relix_0.1.0.tar.gz


