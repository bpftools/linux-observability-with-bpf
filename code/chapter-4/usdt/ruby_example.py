import argparse
from bcc import BPF, USDT

bpf_source = """
#include <uapi/linux/ptrace.h>
int trace_latency(struct pt_regs *ctx) {
  char method[64];
  u64 latency;

  bpf_usdt_readarg_p(1, ctx, &method, sizeof(method));
  bpf_usdt_readarg(2, ctx, &latency);

  bpf_trace_printk("method %s took %d ms", method, latency);
}
"""

parser = argparse.ArgumentParser()
parser.add_argument("-p", "--pid", type = int, help = "Process ID")
args = parser.parse_args()

usdt = USDT(pid = int(args.pid))
usdt.enable_probe(probe = "latency", fn_name = "trace_latency")
bpf = BPF(text = bpf_source, usdt = usdt)
bpf.trace_print()
