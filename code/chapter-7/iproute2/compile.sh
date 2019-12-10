#!/bin/bash
clang -g -c -O2 -target bpf -c program.c -o program.o
