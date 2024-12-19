set -euo pipefail

Rscript -e "Rcpp::compileAttributes()"
R CMD build .
R CMD INSTALL --clean Relix_0.1.0.tar.gz

