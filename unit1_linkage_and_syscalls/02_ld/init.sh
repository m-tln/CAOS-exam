#!/bin/bash


g++ -c main.cpp
ld main.o /usr/lib/x86_64-linux-gnu/libstdc++.so.6 /usr/lib/x86_64-linux-gnu/libc.so.6 /usr/lib/gcc/x86_64-linux-gnu/13/crtend.o /usr/lib/gcc/x86_64-linux-gnu/13/crtbegin.o -I /usr/lib64/ld-linux-x86-64.so.2
rm main.o
