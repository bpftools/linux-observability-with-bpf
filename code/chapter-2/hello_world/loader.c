#include "bpf_load.h"
#include <stdio.h>
#include <uapi/linux/bpf.h>

int main(int argc, char **argv) {
  if (load_bpf_file("hello_world_kern.o") != 0) {
    printf("The kernel didn't load the BPF program\\n");
    return -1;
  }

  read_trace_pipe();

  return 0;
}
