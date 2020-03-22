#!/usr/bin/python
import errno
import signal
import sys
from time import sleep

from bcc import BPF, PerfSWConfig, PerfType


def signal_ignore(signal, frame):
    print()


bpf_source = """
#include <uapi/linux/ptrace.h>
#include <uapi/linux/bpf_perf_event.h>
#include <linux/sched.h>

struct trace_t {
  int stack_id;
};

BPF_HASH(cache, struct trace_t);
BPF_STACK_TRACE(traces, 10000);
"""

bpf_source += """
int collect_stack_traces(struct bpf_perf_event_data *ctx) {
  u32 pid = bpf_get_current_pid_tgid() >> 32;
  if (pid != PROGRAM_PID)
    return 0;

  struct trace_t trace = {
    .stack_id = traces.get_stackid(&ctx->regs, BPF_F_USER_STACK)
  };

  cache.increment(trace);
  return 0;
}
"""

program_pid = int(sys.argv[1])
bpf_source = bpf_source.replace('PROGRAM_PID', str(program_pid))

bpf = BPF(text=bpf_source)
bpf.attach_perf_event(ev_type=PerfType.SOFTWARE,
                      ev_config=PerfSWConfig.CPU_CLOCK,
                      fn_name='collect_stack_traces',
                      sample_period=1)

exiting = 0
try:
    sleep(300)
except KeyboardInterrupt:
    exiting = 1
    signal.signal(signal.SIGINT, signal_ignore)

print("dumping the results")
for trace, acc in sorted(bpf['cache'].items(), key=lambda cache: cache[1].value):
    line = []
    if trace.stack_id < 0 and trace.stack_id == -errno.EFAULT:
        line = ['Unknown stack']
    else:
        stack_trace = list(bpf['traces'].walk(trace.stack_id))
        for stack_address in reversed(stack_trace):
            function_name = bpf.sym(stack_address, program_pid).decode('utf-8')
            if function_name == '[unknown]':
                continue
            line.extend([function_name])

    if len(line) < 1:
        continue
    frame = ";".join(line)
    sys.stdout.write("%s %d\n" % (frame, acc.value))
    if exiting:
        exit()
