#!/bin/bash
set -euo pipefail

cmake --preset default -DUSE_R_LIBS=OFF && cmake --build ./build -- -j4
