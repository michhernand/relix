cmake_minimum_required(VERSION 3.11)
project(relix CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
include(CTest)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

find_package(Armadillo REQUIRED)

if(APPLE)
	find_library(ACCELERATE_FRAMEWORK accelerate)
	if (${ACCELERATE_FRAMEWORK})
		SET(ADDITIONAL_LIBS ${ACCELERATE_FRAMEWORK})
	endif()
endif()

add_subdirectory(extern/carma)

option(
	USE_R_LIBS 
	"enable Rcpp and RcppArmadillo include paths for development" 
	OFF
)

option(
	USE_PY_LIBS
	"enable Python bindings"
	OFF
)

if(USE_R_LIBS)
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
else()
	add_library(relix_lib INTERFACE)
endif()

target_include_directories(relix_lib INTERFACE
	${CMAKE_SOURCE_DIR}/inst/include ${ARMADILLO_INCLUDE_DIRS}
)

if (USE_PY_LIBS)
	# if (NOT TARGET armadillo::armadillo)
	# 	add_library(armadillo::armadillo INTERFACE IMPORTED)
	# 	set_target_properties(armadillo::armadillo PROPERTIES
	# 		INTERFACE_INCLUDE_DIRECTORIES "${ARMADILLO_INCLUDE_DIRS}"
	# 		INTERFACE_LINK_LIBRARIES "${ARMADILLO_LIBRARIES}"
	# 	)
	# endif()
	add_subdirectory(py)
else()
	target_link_libraries(relix_lib INTERFACE
		${ARMADILLO_LIBRARIES}
		${ADDITIONAL_LIBS}
	)
endif()



# add_subdirectory(tests/cpp)
