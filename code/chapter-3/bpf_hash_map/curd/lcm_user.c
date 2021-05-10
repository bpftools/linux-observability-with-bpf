//https://blog.csdn.net/alex_yangchuansheng/article/details/108332511
#include <bpf/bpf.h>
#include "bpf_util.h"
#include "bpf_load.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (load_bpf_file("lcm_kern.o") != 0) {
    printf("The kernel didn't load the BPF program\n");
    return -1;
  }
  

 	//read_trace_pipe();
  int result;
  int lookup_key,next_key;
  int value;
  
  while (1)
    {
	lookup_key = next_key = 0;

        sleep(2);
        // retrieve the bpf map of statistics
        while (bpf_map_get_next_key(map_fd[0], &lookup_key, &next_key) != -1)
    	{
		
 
            // get the value via the key
            // TODO: change to assert
            // assert(bpf_map_lookup_elem(map_fd[0], &next_key, &value) == 0)
            result = bpf_map_lookup_elem(map_fd[0], &next_key, &value);
            if (result == 0)
            {
                // print the value
                printf("Value read from the map: '%d'\n", value);
            }
            else
            {
                printf("Failed to read value from the map: %d (%s)\n", result, strerror(errno));
            }
            lookup_key = next_key;
            printf("\n\n");

	}
    }
  return 0;
}
