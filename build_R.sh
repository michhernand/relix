Rscript -e "Rcpp::compileAttributes()"
R CMD build .
R CMD INSTALL --clean --verbose Relix_1.0.tar.gz

