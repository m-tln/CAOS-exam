#!/bin/bash

g++ -shared lib.cpp -o libsqr.so
g++ main.cpp -lsqr -L.
LD_LIBRARY_PATH=. ./a.out


#g++ test.cpp -lsqr -L. -Wl,-rpath,/.