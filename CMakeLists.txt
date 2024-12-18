cmake_minimum_required(VERSION 3.11)
project(relix CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Armadillo REQUIRED)
# find_package(BLAS REQUIRED)
# find_package(LAPACK REQUIRED)

file(GLOB_RECURSE RELIX_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(relix_lib ${RELIX_SOURCES})

target_include_directories(relix_lib PUBLIC 
	${CMAKE_SOURCE_DIR}/include ${ARMADILLO_INCLUDE_DIRS}
)

target_link_libraries(relix_lib PUBLIC 
	${ARMADILLO_LIBRARIES}
)

# Pass BLAS/LAPACK libraries to tests directory
# set(BLAS_LIBRARIES ${BLAS_LIBRARIES} CACHE INTERNAL "BLAS Libraries")
# set(LAPACK_LIBRARIES ${LAPACK_LIBRARIES} CACHE INTERNAL "LAPACK Libraries")

add_subdirectory(tests)
