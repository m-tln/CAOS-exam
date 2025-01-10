#!/bin/bash

g++ -g main.cpp
objdump -d a.out

gdb ./a.out


#/var/lib/apport/coredump
#ulimit -c unlimited
#gdb ./a.out path-to-core-file