//https://github.com/torvalds/linux/commit/bc1a85977b950407d67cd1e5b74f261a4bee3284#diff-827240a4cc1850f5f6869f9d9df3b580ebee719ee0a83ae1f6f4c579b47dd10c  change bpf_load to libbpf
#include <bpf/bpf.h>
#include "bpf_util.h"
#include "bpf_load.h"
#include <stdio.h>

#include "bpf_insn.h"
char bpf_log_buf[BPF_LOG_BUF_SIZE];
int main(int argc, char **argv) {
	int key = 1;
	int prog_fd;
	struct bpf_insn prog[] = {
	
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	};
	//https://github.com/torvalds/linux/blob/5bfc75d92efd494db37f5c4c173d3639d4772966/samples/bpf/sock_example.c
        prog_fd = bpf_load_program(BPF_PROG_TYPE_TRACEPOINT, prog, sizeof(prog) / sizeof(struct bpf_insn), "GPL", 0, bpf_log_buf, BPF_LOG_BUF_SIZE);
 if (prog_fd < 0) {
printf("failed to load prog '%s'\n", strerror(errno));
return -1;
 }
	if (load_bpf_file("lcm_func_kern.o") != 0) {
		printf("The kernel didn't load the BPF program\n"); 
		return -1;

	};
	
	bpf_map_update_elem(map_fd[0], &key, &prog_fd, BPF_ANY);
read_trace_pipe();
	return 0;
} 
