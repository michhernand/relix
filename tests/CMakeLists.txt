cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

add_executable(relix_test
	src/test_main.cpp
	src/test_algo_naive.cpp
	src/test_algo_last.cpp
	src/test_model.cpp
)

target_link_libraries(relix_test PRIVATE 
	Catch2::Catch2WithMain
	relix_lib
	# ${BLAS_LIBRARIES}
	# ${LAPACK_LIBRARIES}
)

target_include_directories(relix_test PRIVATE
	${CMAKE_SOURCE_DIR}/include
)
catch_discover_tests(relix_test)
