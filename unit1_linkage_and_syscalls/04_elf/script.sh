#!/bin/bash

g++ -c test.cpp
readelf -h test.o # REL
rm test.o

g++ -shared test.cpp -o lib.so
readelf -h lib.so # DYN
rm lib.so

g++ -static test.cpp
readelf -h a.out # EXEC

g++ test.cpp
readelf -h a.out # DYN
rm a.out