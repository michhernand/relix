// This file includes/modifies Armadillo code
// Copyright 2008-2024 Conrad Sanderson (https://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
// Copyright 2017-2024 Data61 / CSIRO
// Licensed under Apache License 2.0 (see LICENSE_Armadillo.txt)
//
// This file uses Boost library code
// Copyright Beman Dawes, David Abrahams, 1998-2005.
// Copyright Rene Rivera 2004-2007.
// Licensed under Boost Software License 1.0 (see LICENSE_Boost.txt)
//
#define ARMA_64BIT_WORD

#include <string>
#include <vector>
#include <memory>
#include <carma>
#include <armadillo>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/pytypes.h>
#include "relix.h"

namespace py = pybind11;

py::array relix(
		arma::dmat& x, 
		arma::dvec& y,
		std::string type
) {
	bool intercept { true };
	std::vector<std::string> headers;

	std::unique_ptr<RelimpAlgorithm> ra; 

	if (type == "last") {
		ra = std::make_unique<LastRelimpAlgorithm>(true, std::vector<std::string>{});
	} else if (type == "first") {
		ra = std::make_unique<FirstRelimpAlgorithm>(true, std::vector<std::string>{});
	} else {
		throw py::value_error("Invalid type argument");
		return py::array_t<double>(0);

	}

	return carma::col_to_arr(ra->evaluate_columns(x, y));
}

PYBIND11_MODULE(relix_py, m) {
    m.doc() = "Relix Pybind11 Binding"; 
    m.def("relix_cpp", &relix, "Function to perform relix calculations",
          py::arg("x"), py::arg("y"), py::arg("type"));
}
