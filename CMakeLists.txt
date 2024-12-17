cmake_minimum_required(VERSION 3.11)
project(relix CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
	relix_lib 
	src/impy.cpp
	src/utilities/column_contribution.cpp
	src/utilities/sort.cpp
	src/algos/algo_base.cpp
	src/algos/algo_naive.cpp
)

target_include_directories(relix_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(tests)

# add_executable(relix_test tests/src/test_main.cpp)
#
# target_link_libraries(relix_test PRIVATE relix_lib Catch2::Catch2WithMain)
#
# include(CTest)
#
# add_test(NAME basic_test COMMAND relix_test)

