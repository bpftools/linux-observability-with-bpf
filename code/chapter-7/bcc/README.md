# Chapter 7: XDP and BCC

- A full description of this example can be found in Chapter 7.
- Please remember that the examples here are tested in the Vagrant machine. Please read more in [README.md](/README.md).
- Make sure to change the example accordingly if you wish to build somewhere else, open an issue if you have problems doing so!
- All the dependencies are already handled if you followed the instructions in the main [README.md](/README.md).

In the machine:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-7/bcc
```

In this folder, we have two files: `loader.py` and `program.c`. The last one is the actual program that we are
going to compile and run, it just counts packets in a map and drops any TCP packet.

We don't need to compile it because, since we are using BCC, compilation is handled by BCC itself at loading.

Our loader, `loader.py` can be invoked with:

Nota Bene: make sure to modify the loader `device` variable based on your needs. In the Vagrant environment, we have `eth0` and `eth1`. We used `eth1` because we are dropping TCP packets and we are connected to the instance trough TCP!

```
sudo ./loader.py
```

The program will now hang and will wait for output. When you `CTRL+C` it it will stop and unload the program automatically.

Now that we have the program loaded, we can send some packets trough the `eth1` interface, a ping to the host instance
can be a good way to try.

If we issue a ping:
```bash
ping 192.168.33.1
```

We immediatelly see that the program starts printing results.
```
Printing packet counts per IP protocol-number, hit CTRL+C to stop
0: 1 pkt/s
1: 1 pkt/s
0: 0 pkt/s
1: 1 pkt/s
0: 0 pkt/s
1: 1 pkt/s
0: 0 pkt/s
```

Where zero is just the default value for when there's no data and `1` is the value for ICMP
packets. See the [Wikipedia page: List of IP protocol numbers](https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers) for reference.

