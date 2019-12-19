#!/bin/bash

TOOLS=/kernel-src/samples/bpf
INCLUDE=/kernel-src/tools/lib
PERF_INCLUDE=/kernel-src/tools/perf
KERNEL_TOOLS_INCLUDE=/kernel-src/tools/include/
LIBRARY_PATH=/urs/local/lib64/
BPFSO=bpf

export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/lib64
clang -o loader -lelf\
  -I${INCLUDE} \
  -I${PERF_INCLUDE} \
  -I${KERNEL_TOOLS_INCLUDE} \
  -I${TOOLS} \
  -l${BPFSO}\
  ${TOOLS}/bpf_load.c \
  loader.c
