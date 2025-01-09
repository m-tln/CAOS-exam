#!/bin/bash

g++ -static -o main main.cpp
objdump -d main | grep svc
rm main