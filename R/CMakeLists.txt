cmake_minimum_required(VERSION 3.11)

message(STATUS "Adding Rcpp and RcppArmadillo include paths")
execute_process(
	COMMAND Rscript ${CMAKE_SOURCE_DIR}/Rscripts/rcpp_includes.R
	OUTPUT_VARIABLE RCPP_INCLUDE_PATHS
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REPLACE " " ";" RCPP_INCLUDES ${RCPP_INCLUDE_PATHS})
include_directories(${RCPP_INCLUDES})
message(STATUS "Rcpp include paths: ${RCPP_INCLUDES}")

add_library(relix_lib
	src/relix_r.cpp
)

