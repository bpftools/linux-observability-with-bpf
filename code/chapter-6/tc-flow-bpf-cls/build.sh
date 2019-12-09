#!/bin/bash
clang  -g -c -O2 -target bpf -c classifier.c -o classifier.o
