#!/bin/bash

sh ./clean.sh
mkdir ./build
cd build && cmake .. -DUSE_R_LIBS=OFF
cmake --build . -- -j4
./tests/relix_test
