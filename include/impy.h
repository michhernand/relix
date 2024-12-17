#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define IMPY_EXPORT __declspec(dllexport)
#else
  #define IMPY_EXPORT
#endif

IMPY_EXPORT void impy();
IMPY_EXPORT void impy_print_vector(const std::vector<std::string> &strings);
