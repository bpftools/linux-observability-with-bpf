# Chapter 6: Packet filtering with Raw Sockets

- A full description of this example can be found in Chapter 6.
- Please remember that the examples here are tested in the Vagrant machine. Please read more in [README.md](/README.md).
- Make sure to change the example accordingly if you wish to build somewhere else, open an issue if you have problems doing so!
- All the dependencies are already handled if you followed the instructions in the main [README.md](/README.md).

In the machine:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-6/packet-filtering-raw-sockets
```

Compile the loader

```bash
./build-loader.sh /kernel-src
```

It will create a binary file named `loader-bin`

Compile the program

```bash
./build-bpf-program.sh
```
It will create a BPF ELF named `bpf-program.o`


Execute the program using the loader:

```
sudo ./loader-bin bpf_program.o 
```

It will show something like this, ten results, one every second for ten seconds:

```
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 0 packets
TCP 0 UDP 0 ICMP 4 packets
TCP 0 UDP 0 ICMP 8 packets
TCP 0 UDP 0 ICMP 12 packets
TCP 0 UDP 0 ICMP 16 packets
TCP 0 UDP 0 ICMP 16 packets
TCP 0 UDP 0 ICMP 16 packets
```

Since the program is attached to the loopback interface `lo` (see `loader.c` line 30) we need to generate traffic on
that interface to show the packets flow.

You can simply do a ping to localhost in the VM while the program is running.

```
ping 127.0.0.1
```
