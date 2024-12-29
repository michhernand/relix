cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

file(GLOB_RECURSE RELIX_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(relix_test
	${RELIX_TESTS}
)

target_link_libraries(relix_test PRIVATE 
	Catch2::Catch2WithMain
	relix_lib
)

target_include_directories(relix_test PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(relix_test PRIVATE
	TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
)

catch_discover_tests(relix_test
	REPORTER CONSOLE
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
