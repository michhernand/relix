cmake_minimum_required(VERSION 3.11)
project(relix CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Armadillo REQUIRED)

if(APPLE)
	find_library(ACCELERATE_FRAMEWORK accelerate)
	if (${ACCELERATE_FRAMEWORK})
		SET(ADDITIONAL_LIBS ${ACCELERATE_FRAMEWORK})
	endif()
endif()


option(
	USE_R_LIBS 
	"enable R bindings"
	OFF
)

option(
	USE_PY_LIBS
	"enable Python bindings"
	OFF
)

option(
	ENABLE_TESTING
	"enable testing"
	OFF
)

if(USE_R_LIBS)
	add_subdirectory(R)
else()
	add_library(relix_lib INTERFACE)
endif()

target_include_directories(relix_lib INTERFACE
	${CMAKE_SOURCE_DIR}/inst/include ${ARMADILLO_INCLUDE_DIRS}
)

if (USE_PY_LIBS)
	add_subdirectory(extern/carma)
	add_subdirectory(py)
else()
	target_link_libraries(relix_lib INTERFACE
		${ARMADILLO_LIBRARIES}
		${ADDITIONAL_LIBS}
	)
endif()

if(ENABLE_TESTING)
	add_subdirectory(tests/cpp)
endif()
