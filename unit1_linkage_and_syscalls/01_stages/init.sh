#!/bin/bash

g++ -E main.cpp > /dev/null
g++ -S main.cpp
g++ -c main.cpp
g++ main.o

readelf -h main.o

readelf -s a.out

rm main.s
rm main.o
rm a.out