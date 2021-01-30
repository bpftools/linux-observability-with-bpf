#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>

#include "bpf_load.h"
#include "bpf_util.h"
#include "libbpf.h"

static const char *file_path = "/sys/fs/bpf/my_array";

int main(int argc, char **argv) {
  int fd, key, value, result;

  fd = bpf_obj_get(file_path);
  if (fd < 0) {
    printf("Failed to fetch the map: %d (%s)\n", fd, strerror(errno));
    return -1;
  }

  key = 1;
  result = bpf_map_lookup_elem(fd, &key, &value);
  if (result < 0) {
    printf("Failed to read value from the map: %d (%s)\n", result,
           strerror(errno));
    return -1;
  }

  printf("Value read from the map: '%d'\n", value);
  return 0;
}
