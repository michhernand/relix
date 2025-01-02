cmake_minimum_required(VERSION 3.11) 

OPTION(CLEAN "clean up files/folders" OFF)
OPTION(FILES_ONLY "clean files only" OFF)
OPTION(FOLDERS_ONLY "clean folders only" OFF)

OPTION(R_BUILD "build R library" OFF)
OPTION(COMPILE_ATTRS "compile attributes" ON)
OPTION(COMPILE_DOCS "compile documentation" ON)
OPTION(BUILD_R "build r package" ON)
OPTION(INSTALL_R "install r package" ON)



IF(${CLEAN})
	INCLUDE(${CMAKE_SOURCE_DIR}/scripts/clean.cmake)

	IF(NOT ${FILES_ONLY})
		delete_dir(${CACHE_DIR})
		delete_dir(${BUILD_DIR})
		delete_dir(${DEPS_DIR})
		delete_dir(${RCMD_CHECK_DIR})
	ENDIF()

	IF(NOT ${FOLDERS_ONLY})
		delete_files(${CACHE_FILES})
		delete_files(${TEMP_FILES})
	ENDIF()
ENDIF()

IF(${R_BUILD})
	INCLUDE(${CMAKE_SOURCE_DIR}/scripts/r_build.cmake)

	IF(${COMPILE_ATTRS})
		compile_attributes()
	ENDIF()

	IF(${COMPILE_DOCS})
		compile_documentation()
	ENDIF()

	IF(${BUILD_R})
		build_r_lib()
	ENDIF()

	IF(${INSTALL_R})
		install_r_lib()
	ENDIF()
ENDIF()

# IF (${TEST})
# 	ctest --test-dir ./build --output-on-failure
# ENDIF()