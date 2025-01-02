function(compile_attributes)
	message(STATUS "Recompiling Attributes")
	execute_process(
		COMMAND Rscript -e "Rcpp::compileAttributes()"
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		RESULT_VARIABLE rcmd_compile_result
		OUTPUT_VARIABLE rcmd_compile_output
		ERROR_VARIABLE rcmd_compile_error
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_STRIP_TRAILING_WHITESPACE
	)

	IF(${rcmd_compile_result} EQUAL 0)
		message(STATUS "Compiled Attributes (SUCCESSFUL)")
	ELSE()
		message(WARN ${rcmd_compile_result})
		message(FATAL_ERROR "Compilation of Attributes (FAILED STATUS!=0)")
	ENDIF()
endfunction()

function(compile_documentation)
	message(STATUS "Recompiling Docs")
	execute_process(
		COMMAND Rscript -e "devtools::document()"
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		RESULT_VARIABLE rcmd_doc_result
		OUTPUT_VARIABLE rcmd_doc_output
		ERROR_VARIABLE rcmd_doc_error
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_STRIP_TRAILING_WHITESPACE
	)

	IF(${rcmd_doc_result} EQUAL 0)
		message(STATUS "Compiled Docs (SUCCESSFUL)")
	ELSE()
		message(WARN ${rcmd_doc_result})
		message(FATAL_ERROR "Compilation of Docs (FAILED STATUS!=0)")
	ENDIF()
endfunction()

function(build_r_lib)
	message(STATUS "Building R Library")
	execute_process(
		COMMAND R CMD BUILD .
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		RESULT_VARIABLE rcmd_build_result
		OUTPUT_VARIABLE rcmd_build_output
		ERROR_VARIABLE rcmd_build_error
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_STRIP_TRAILING_WHITESPACE
	)

	IF(${rcmd_build_result} EQUAL 0)
		STRING(
			REGEX MATCH
			"relix_.*\\.tar.gz"
			rcmd_package
			${rcmd_build_output}
		)

		IF(${rcmd_package})
			message(FATAL_ERROR "Build of R Library (FAILED STATUS!=0)")
		ENDIF()
		SET(rcmd_package "${rcmd_package}" PARENT_SCOPE)
		message(STATUS "Built ${rcmd_package} (SUCCESSFUL)")
	ELSE()
		message(WARN ${rcmd_build_result})
		message(FATAL_ERROR "Build of R Library (FAILED STATUS!=0)")
	ENDIF()
endfunction()

function(install_r_lib)
	message(STATUS "Installing ${rcmd_package}")
	execute_process(
		COMMAND R CMD INSTALL --clean --preclean ${rcmd_package}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		RESULT_VARIABLE rcmd_install_result
		OUTPUT_VARIABLE rcmd_install_output
		ERROR_VARIABLE rcmd_install_error
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_STRIP_TRAILING_WHITESPACE
	)

	IF(${rcmd_install_result} EQUAL 0)
		message(STATUS "Installed ${rcmd_package} (SUCCESSFUL)")
	ELSE()
		message(WARN ${rcmd_install_result})
		message(FATAL_ERROR "Install of R Library (FAILED STATUS!=0)")
	ENDIF()
endfunction()
