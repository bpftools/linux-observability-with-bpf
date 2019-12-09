# Chapter 6: BPF-Based Traffic Control Classifier

A full description of this example can be found in Chapter 6.

Before reading this, make sure you follow the instructions to create the  Vagrant machine so all the dependencies are already handled, see the main [README.md](/README.md).

In the vagrant machine:

Enter into this example folder:

```bash
cd /vagrant/code/chapter-6/tc-flow-bpf-cls
```

Build the program

```bash
./build.sh
```

It will create an ELF file named `classifier.o`

Now, since this example is using Traffic Control as a loader, we don't need to build a loader
ourselves but we just use the `load.sh` script that uses `tc` to load the program on an interface
passed as first argument.

You can use it like this on the loopback (`eth0`), or any other interface (`lo`, `eth1` etc..):

```bash
sudo ./load.sh eth0
```

Since the program `classifier.c` writes with `bpf_trace_printk` it will dump the output to `/sys/kernel/debug/tracing/trace_pipe`.

The classifier is written in a way that everytime an HTTP packet goes trough that interface it will print `Yes! It is HTTP!`.

If you now do an http request to any HTTP server, e.g

```bash
curl http://bpf.sh
```

It will show:

```
[vagrant@bpfbook tc-flow-bpf-cls]$ sudo cat /sys/kernel/debug/tracing/trace_pipe
          <idle>-0     [000] ..s. 30096.619165: 0: Yes! It is HTTP!
```


At this point, you will want to unload the program, to do so:

```bash
sudo ./unload.sh eth0
```
