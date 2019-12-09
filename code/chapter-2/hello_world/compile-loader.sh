#!/bin/bash

TOOLS=/kernel-src/samples/bpf
INCLUDE=/kernel-src/tools/lib
PERF_INCLUDE=/kernel-src/tools/perf
KERNEL_TOOLS_INCLUDE=/kernel-src/tools/include/
clang -o loader -lelf\
  -I${INCLUDE} \
  -I${PERF_INCLUDE} \
  -I${KERNEL_TOOLS_INCLUDE} \
  -I${TOOLS} \
  ${TOOLS}/bpf_load.c \
  loader.c
