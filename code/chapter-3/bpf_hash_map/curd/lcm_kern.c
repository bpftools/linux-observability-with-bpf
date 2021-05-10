





#include <linux/version.h>
#include <linux/ptrace.h>
#include <uapi/linux/bpf.h>
#include "bpf_helpers.h"

//#include "bpf_helpers.h"
//#include <linux/bpf.h>
//#include "bpf_endian.h"
//#define SEC(NAME) __attribute__((section(NAME), used))


struct bpf_map_def SEC("maps") hash_map = {
	.type = BPF_MAP_TYPE_HASH,
	.key_size = sizeof(u32),
	.value_size = sizeof(long),
	.max_entries = 2,
};


//struct bpf_map_def SEC("maps") learn_map = {
//    .type = BPF_MAP_TYPE_HASH,
//    .key_size = sizeof(int),
//    .value_size = sizeof(int),
//    .max_entries = 2
//};


//static int (*bpf_trace_printk)(const char *fmt, int fmt_size,
//                               ...) = (void *)BPF_FUNC_trace_printk;

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  
  int key = 1;
int value = 1024;
  bpf_map_update_elem(&hash_map, &key, &value, BPF_ANY);
  char msg[] = "Hello, BPF World!";
  bpf_trace_printk(msg, sizeof(msg));
  return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;

