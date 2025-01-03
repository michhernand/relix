cmake_minimum_required(VERSION 3.11)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(Armadillo REQUIRED)

pybind11_add_module(relix_py ${CMAKE_SOURCE_DIR}/src/relix_py.cpp)

target_link_libraries(relix_py PRIVATE
    relix_lib
    carma::carma
    ${ARMADILLO_LIBRARIES}
)

target_include_directories(relix_py PRIVATE
    ${CMAKE_SOURCE_DIR}/inst/include
)
