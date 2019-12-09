#!/bin/bash
TOOLS=../../../tools
INCLUDE=../../../libbpf/include
HEADERS=../../../libbpf/src
clang -o loader -l elf \
  -I${INCLUDE} \
  -I${HEADERS} \
  -I${TOOLS} \
  ${TOOLS}/bpf_load.c \
  loader.c
