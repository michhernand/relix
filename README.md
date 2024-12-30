# Relix

Relix is a library to compute the relative importance of predictors in a linear regression. 

This software is built using the methodology and principles of Relative Importance developed by Ulrike Groemping (Groemping, U. (2006). Relative Importance for Linear Regression in R: The Package relaimpo. Journal of Statistical Software, 17(1), 1–27. <doi:10.18637/jss.v017.i01>).

# C++ Library
## Installation
### Pre-Compiled Distributions
- TBD
### Build From Source
#### Requirements
- [cmake](https://cmake.org)
- [vcpkg](https://vcpkg.io/)

#### Steps
- `mkdir build`
- `cmake -DUSE_R_LIBS=OFF --preset=default`
- `cmake --build ./build`

# R Library
## Installation
### Option 1: Pre-Compiled Distributions
- TBD
### Option 2: CMake Script
#### Requirements
- [R](https://cran.r-project.org)
- [cmake](https://cmake.org)
- C++ Compiler
#### Steps
- cmake -DR_BUILD=ON -P ./builder.cmake
### Option 3: Manual Compilation
#### Requirements
- [R](https://cran.r-project.org)
- C++ Compiler
#### Steps
- `R CMD BUILD .`
- `R CMD INSTALL relix_x.xx.tar.gz`
## Removal
- To uninstall, run `Rscript -e "remove.packages('relix')"`
