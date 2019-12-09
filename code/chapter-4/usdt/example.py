from bcc import BPF, USDT

bpf_source = """
#include <uapi/linux/ptrace.h>
int trace_binary_exec(struct pt_regs *ctx) {
  u64 pid = bpf_get_current_pid_tgid();
  bpf_trace_printk("New hello_usdt process running with PID: %d", pid);
}
"""

usdt = USDT(path = "./hello_usdt")
usdt.enable_probe(probe = "probe-main", fn_name = "trace_binary_exec")
bpf = BPF(text = bpf_source, usdt = usdt)
bpf.trace_print()
