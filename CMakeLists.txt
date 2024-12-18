cmake_minimum_required(VERSION 3.11)
project(relix CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Armadillo REQUIRED)

file(GLOB_RECURSE RELIX_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(relix_lib ${RELIX_SOURCES})

target_include_directories(relix_lib PUBLIC 
	${CMAKE_SOURCE_DIR}/include ${ARMADILLO_INCLUDE_DIRS}
)

target_link_libraries(relix_lib PUBLIC 
	${ARMADILLO_LIBRARIES}
)

add_subdirectory(tests)
