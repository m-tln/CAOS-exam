#!/bin/bash

g++ -static -o main main.cpp
objdump -d main | grep syscall
rm main
