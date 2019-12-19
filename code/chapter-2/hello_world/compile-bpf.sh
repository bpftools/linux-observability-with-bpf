#!/bin/bash
export C_INCLUDE_PATH=/kernel-src/tools/testing/selftests/bpf
clang -O2 -target bpf \
  -c bpf_program.c \
  -o hello_world_kern.o
