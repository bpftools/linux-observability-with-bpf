from bcc import BPF

bpf_source = """
#include <linux/sched.h>
#include <uapi/linux/ptrace.h>

struct data_t {
    char comm[TASK_COMM_LEN];
};

BPF_PERF_OUTPUT(events);

int do_sys_execve(struct pt_regs *ctx) {
  struct data_t data = {};
  bpf_get_current_comm(&data.comm, sizeof(data.comm));
  events.perf_submit(ctx, &data, sizeof(data));
  return 0;
}
"""

bpf = BPF(text = bpf_source)
execve_function = bpf.get_syscall_fnname("execve")
bpf.attach_kprobe(event = execve_function, fn_name = "do_sys_execve")

from collections import Counter
aggregates = Counter()

def aggregate_programs(cpu, data, size):
  event = bpf["events"].event(data)
  aggregates[event.comm] += 1

bpf["events"].open_perf_buffer(aggregate_programs)
while True:
    try:
      bpf.perf_buffer_poll()
    except KeyboardInterrupt:
      break

for (comm, times) in aggregates.most_common(): 
  print("Program {} executed {} times".format(comm, times))
