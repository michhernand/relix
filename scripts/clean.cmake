cmake_minimum_required(VERSION 3.11) 
OPTION(FILES_ONLY "clean files only" OFF)
OPTION(FOLDERS_ONLY "clean folders only" OFF)


SET(BUILD_DIR "build" CACHE STRING "build directory")
SET(CACHE_DIR ".cache" CACHE STRING "cache directory")
SET(DEPS_DIR "_deps" CACHE STRING "_deps directory")
SET(RCMD_CHECK_DIR "relix.Rcheck" CACHE STRING "R CMD check directory")

SET(
	CACHE_FILES
	"CMakeCache.txt;cmake_install.cmake;compile_commands.json;CMakeFiles;*.o;*.so;*.a;*.log;relix_*.tar.gz;tests/relix_test"
	CACHE INTERNAL
	"build cache files"
)

SET(
	TEMP_FILES
	"*~;*.swp;*.bak"
	CACHE INTERNAL
	"build temp files"
)

function(delete_dir folder_name)
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

function(delete_files file_list)
	foreach(fp IN LISTS file_list)
		STRING(CONCAT ABS_FP ${CMAKE_SOURCE_DIR} / ${fp})

		if(EXISTS "${ABS_FP}")
			message(STATUS "Removing file: ${ABS_FP}")
			file(REMOVE "${ABS_FP}")
		else()
			message(STATUS "No file found at: ${ABS_FP}")
		endif()
	endforeach()
endfunction()

IF(${CLEAN})
	delete_dir(${CACHE_DIR})
	delete_dir(${BUILD_DIR})
	delete_dir(${DEPS_DIR})
	delete_dir(${RCMD_CHECK_DIR})

	delete_files(${CACHE_FILES})
	delete_files(${TEMP_FILES})
ENDIF()
