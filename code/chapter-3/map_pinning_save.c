#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>

#include "bpf_load.h"
#include "bpf_util.h"
#include "libbpf.h"

static const char *file_path = "/sys/fs/bpf/my_array";

int main(int argc, char **argv) {
  int key, value, fd, added, pinned;

  fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, sizeof(int), sizeof(int), 100, 0);
  if (fd < 0) {
    printf("Failed to create map: %d (%s)\n", fd, strerror(errno));
    return -1;
  }

  key = 1, value = 1234;
  added = bpf_map_update_elem(fd, &key, &value, BPF_ANY);
  if (added < 0) {
    printf("Failed to update map: %d (%s)\n", added, strerror(errno));
    return -1;
  }

  pinned = bpf_obj_pin(fd, file_path);
  if (pinned < 0) {
    printf("Failed to pin map to the file system: %d (%s)\n", pinned,
           strerror(errno));
    return -1;
  }

  return 0;
}
