cmake_minimum_required(VERSION 3.11)


find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(relix_py ${CMAKE_SOURCE_DIR}/src/relix_py.cpp)

target_link_libraries(relix_py PRIVATE
    relix_lib
    carma::carma
    ${ARMADILLO_LIBRARIES}
)

target_include_directories(relix_py PRIVATE
    ${CMAKE_SOURCE_DIR}/inst/include
)

add_custom_command(TARGET relix_py
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:relix_py> ${CMAKE_SOURCE_DIR}/py/relix
)
