# Chapter 7: XDP and iproute2 as a loader

A full description of this example can be found in Chapter 7. It contains shows how to use this program against a webserver and has a full explanation of the arguments used. Please refer to the book.

Before reading this, make sure you follow the instructions to create the  Vagrant machine so all the dependencies are already handled, see the main [README.md](/README.md).

In the vagrant machine:

Enter into this example folder:

```bash
cd /vagrant/code/chapter-7/iproute2
```

You can now use the `compile.sh` script to create the `program.o` ELF file.


Now that you have it, you can load the program to an interface. We will use `eth1` again because the program
blocks TCP packets and we are connected to the Vagrant machine trough SSH :)

```bash
sudo ip link set dev eth1 xdp obj program.o sec mysection
```


Please note that you can see that the program was loaded by doing an `ip a` and looking for `xdpgeneric` in the `eth` network interface.


To unload the program you have to do:

```bash
sudo ip link set dev eth1 xdp off
```
