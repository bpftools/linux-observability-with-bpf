<p><img align="right" src="/img/owl.png" width="150px"/></p>
<p></p>

# Linux Observability with BPF code examples

This is the companion code repo for the book [Linux Observability with BPF](https://bit.ly/bpf-safari).

We believe that even if the examples included in the book were all tested and working when we wrote them, human error is possible and technology changes.
For that reason, the purpose of this repo is to keep them as updated as possible and correct mistakes we made while writing the book.


## Code examples

### Chapter 2

- [Hello World](/code/chapter-2/hello_world)

### Chapter 3

- [The BPF Virtual Filesystem](/code/chapter-3/bpf_fs)

### Chapter 4

#### Probes

##### Kernel Probes
- [Kprobes](/code/chapter-4/kprobes)
- [Kretprobes](/code/chapter-4/kretprobes)

##### User-Space Probes
- [Probes > User-Space Probes > Uprobes](/code/chapter-4/uprobes)
- [Probes > User-Space Probes > Uretprobes ](/code/chapter-4/uretprobes)

##### Tracepoints
- [Tracepoints](/code/chapter-4/tracepoints)

#### User Statically Defined Tracepoints (USDT)
- [User Statically Defined Tracepoints](/code/chapter-4/usdt)

##### Visualizing Tracing Data
- [Flame Graphs](/code/chapter-4/flamegraphs)
- [Histograms](/code/chapter-4/histograms)
- [Perf Events](/code/chapter-4/histograms)

### Chapter 6 - Linux Networking and BPF

- [Packet filtering for raw sockets](/code/chapter-6/packet-filtering-raw-sockets)
- [Traffic control classifier program using cls_bpf](/code/chapter-6/tc-flow-bpf-cls)

### Chapter 7 - eXpress Data Path (XDP)

- [XDP using iproute2 as a loader](/code/chapter-7/iproute2)
- [XDP using BCC as a loader](/code/chapter-7/bcc)
- [Testing XDP programs](/code/chapter-7/prog-test-run)


### Chapter 8 - Linux Kernel security, Capabilities and Seccomp

- [Seccomp BPF filter example](/code/chapter-8/seccomp)
