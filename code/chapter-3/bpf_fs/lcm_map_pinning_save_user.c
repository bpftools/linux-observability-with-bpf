#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>

#include "bpf_load.h"
#include "bpf_util.h"
#include "libbpf.h"

static const char *file_path = "/sys/fs/bpf/lcm/my_dataset";

int main(int argc, char **argv) {
  int key, value,  added, pinned;
//  char* mapName = "lcmdataset";
 // fd = bpf_create_map_name(BPF_MAP_TYPE_ARRAY, mapName, sizeof(int), sizeof(int), 100, 0);
  //if (fd < 0) {
   // printf("Failed to create map: %d (%s)\n", fd, strerror(errno));
    //return -1;
  //}

  if (load_bpf_file("lcm_map_pinning_save_kern.o") != 0) {
	          printf("The kernel didn't load the BPF program\n"); 
		  return -1;
  }


  key = 1, value = 1234;
  added = bpf_map_update_elem(map_data[0].fd, &key, &value, BPF_ANY);
  if (added < 0) {
    printf("Failed to update map: %d (%s)\n", added, strerror(errno));
    return -1;
  }

  sleep(10);
  //also can use get object to get fd, such soktmap
  pinned = bpf_obj_pin(map_data[0].fd, file_path);
  if (pinned < 0) {
    printf("Failed to pin map to the file system: %d (%s)\n", pinned,
           strerror(errno));
    return -1;
  }

  return 0;
}
