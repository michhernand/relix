# Relix

Relix is a library to compute the relative importance of predictors in a linear regression. 

This software is built using the methodology and principles of Relative Importance developed by Ulrike Groemping (Groemping, U. (2006). Relative Importance for Linear Regression in R: The Package relaimpo. Journal of Statistical Software, 17(1), 1–27. <doi:10.18637/jss.v017.i01>).

# Overview
The original "relaimpo" package created by Ulrike Groemping has been immensely impactful. The code and underlying research are a significant contribution to the statistical community.

In the years since its release in 2006, the size of datasets has increased dramatically. Additionally techniques like bootstrapping involve running the same data pipelines repeatedly. Overall, this has resulted in larger data pipelines running on larger datasets. 

Relix was created to:
- Maximize the performance of calculating relative importance.
- Minimize the energy (cost, environmental) impact of calculating relative importance.
- Make relative importance cross-language (R, Python, C++).

# Performance
Benchmarks were invoked from the command line using `Rscript ./Rscripts/benchmark1.R` and `Rscript ./Rscripts/benchmark2.R`. Overall, we can see a significant speed increase.

Note: Unit tests showing accuracy can be found in tests/cpp/src.

## Benchmark 1 (MTCars - Relix is 8.53x Faster)
![Benchmark 1](./images/benchmark1_result.png)

## Benchmark 2 (TLC Trip Record Data - Relix is 19.31x Faster)
![Benchmark 2](./images/benchmark2_result.png)

# C++ Library
## Installation
### Pre-Compiled Distributions
- TBD
### Build From Source
#### Requirements
- [cmake](https://cmake.org)
- [vcpkg](https://vcpkg.io/)
- C++ Compiler

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
- `cmake -DR_BUILD=ON -P ./builder.cmake`
### Option 3: Manual Compilation
#### Requirements
- [R](https://cran.r-project.org)
- C++ Compiler
#### Steps
##### Unix
- `R CMD BUILD .`
- `R CMD INSTALL relix_x.xx.tar.gz`
##### Windows
- `R.exe CMD build .`
- `R.exe CMD INSTALL relix_x.xx.tar.gz`
## Removal
- To uninstall, run `Rscript -e "remove.packages('relix')"`

# Roadmap
- [X] "First" algorithm.
- [X] "Last" algorithm.
- [ ] (In Progress) v0.1 release.
- [ ] R Library on CRAN.
- [ ] Python Library on PyPI.
- [ ] "LMG" algorithm.
