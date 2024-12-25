cmake_minimum_required(VERSION 3.11)
project(relix CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Armadillo REQUIRED)

option(
	USE_R_LIBS 
	"enable Rcpp and RcppArmadillo include paths for development" 
	ON
)

if(USE_R_LIBS)
	message(STATUS "Adding Rcpp and RcppArmadillo include paths")
	execute_process(
		COMMAND Rscript ${CMAKE_SOURCE_DIR}/rcpp_includes.R
		OUTPUT_VARIABLE RCPP_INCLUDE_PATHS
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	string(REPLACE " " ";" RCPP_INCLUDES ${RCPP_INCLUDE_PATHS})
	include_directories(${RCPP_INCLUDES})
	message(STATUS "Rcpp include paths: ${RCPP_INCLUDES}")

	add_library(relix_lib
		src/lm.cpp
		src/utils.cpp
		src/algo_first.cpp
		src/algo_last.cpp
		src/algo_lmg.cpp
		src/relix.cpp
		src/relix_r.cpp
	)
else()
	add_library(relix_lib
		src/lm.cpp
		src/utils.cpp
		src/algo_first.cpp
		src/algo_last.cpp
		src/algo_lmg.cpp
		src/relix.cpp
	)
endif()



target_include_directories(relix_lib PUBLIC 
	${CMAKE_SOURCE_DIR}/inst/include ${ARMADILLO_INCLUDE_DIRS}
)

target_link_libraries(relix_lib PUBLIC 
	${ARMADILLO_LIBRARIES}
)

add_subdirectory(tests)
