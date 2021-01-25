from bcc import BPF

bpf_source = """
int trace_go_main(struct pt_regs *ctx) {
  u64 pid = bpf_get_current_pid_tgid();
  bpf_trace_printk("New hello-bpf process running with PID: %d\\n", pid);
  return 0;
}
"""

bpf = BPF(text = bpf_source)
bpf.attach_uprobe(name = "./hello-bpf", sym = "main.main", fn_name = "trace_go_main")
bpf.trace_print()
