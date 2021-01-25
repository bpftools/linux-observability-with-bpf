from bcc import BPF

bpf_source = """
BPF_HASH(cache, u64, u64);

int trace_start_time(struct pt_regs *ctx) {
  u64 pid = bpf_get_current_pid_tgid();
  u64 start_time_ns = bpf_ktime_get_ns();
  cache.update(&pid, &start_time_ns);
  return 0;
}
"""

bpf_source += """
int print_duration(struct pt_regs *ctx) {
  u64 pid = bpf_get_current_pid_tgid();
  u64 *start_time_ns = cache.lookup(&pid);
  if (start_time_ns == 0) {
    return 0;
  }
  u64 duration_ns = bpf_ktime_get_ns() - *start_time_ns;
  bpf_trace_printk("Function call duration: %d\\n", duration_ns);
  return 0;
}
"""

bpf = BPF(text = bpf_source)
bpf.attach_uprobe(name = "./hello-bpf", sym = "main.main", fn_name = "trace_start_time")
bpf.attach_uretprobe(name = "./hello-bpf", sym = "main.main", fn_name = "print_duration")
bpf.trace_print()
