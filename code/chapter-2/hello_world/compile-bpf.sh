#!/bin/bash
clang -O2 -target bpf \
  -c bpf_program.c \
  -o hello_world_kern.o
