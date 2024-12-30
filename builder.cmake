cmake_minimum_required(VERSION 3.11) 
OPTION(CLEAN "clean project" OFF)


SET(BUILD_DIR "build" CACHE STRING "build directory")
SET(CACHE_DIR ".cache" CACHE STRING "cache directory")
SET(DEPS_DIR "_deps" CACHE STRING "_deps directory")
SET(RCMD_CHECK_DIR "relix.Rcheck" CACHE STRING "R CMD check directory")

SET(
	CACHE_FILES
	"CMakeCache.txt;cmake_install.cmake;compile_commands.json;CMakeFiles;*.o;*.so;*.a;*.log;relix_*.tar.gz"
	CACHE INTERNAL
	"build cache files"
)

SET(
	TEMP_FILES
	"*~;*.swp;*.bak"
	CACHE INTERNAL
	"build temp files"
)

function(delete_if_exists folder_name)
	STRING(CONCAT ABS_DIR ${CMAKE_SOURCE_DIR} "/" ${folder_name})
	IF(EXISTS ${ABS_DIR})
		message("Removing direcotry: " ${ABS_DIR})
		FILE(
			REMOVE_RECURSE
			${ABS_DIR}
		)
	ELSE()
		message("No directory found: " ${ABS_DIR})
	ENDIF()
endfunction()

IF(${CLEAN})
	delete_if_exists(${CACHE_DIR})
ENDIF()
