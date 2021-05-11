





#include <linux/version.h>
#include <linux/ptrace.h>
#include <uapi/linux/bpf.h>
#include "bpf_helpers.h"

//#include "bpf_helpers.h"
//#include <linux/bpf.h>
//#include "bpf_endian.h"
//#define SEC(NAME) __attribute__((section(NAME), used))


struct bpf_map_def SEC("maps") hash_programs = {
	.type = BPF_MAP_TYPE_PROG_ARRAY,
	.key_size = sizeof(u32),
	.value_size = sizeof(u32),
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
	  bpf_tail_call(ctx, &hash_programs, key);
	      char msg[] = "Call failed!";
	        bpf_trace_printk(msg, sizeof(msg));   //参考 https://blog.csdn.net/notbaron/article/details/80256549
	return 0;

}
/*struct bpf_insn prog[] = { 
	BPF_MOV64_IMM(BPF_REG_0, 0),
	 BPF_EXIT_INSN(), 
};
*/

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;

