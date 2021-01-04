# Chapter 7: Testing XDP programs

- A full description of this example can be found in Chapter 7. It explains the various steps better and walks you through the code here.
- Please remember that the examples here are tested in the Vagrant machine. Please read more in [README.md](/README.md).
- Make sure to change the example accordingly if you wish to build somewhere else, open an issue if you have problems doing so!
- All the dependencies are already handled if you followed the instructions in the main [README.md](/README.md).



Before reading this, make sure you follow the instructions to create the  Vagrant machine so all the dependencies are already handled, see the main [README.md](/README.md).

In the vagrant machine:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-7/prog-test-run
```

First let's gather some dependencies.

We already have the BCC python library, coming from the BCC package provisioned in the Vagrantfile, but we need
to install scapy.

```
sudo pip3 install scapy
```

Now we can take a look at our `program.c`, this program has different actions based on the destination
mac address and packet type. What we want to achieve, is to write a test suite to verify that the program behaves correctly.

Our test suite is defined in the `test_xdp.py` program, let's run it:

```bash
sudo python3 test_xdp.py
```

Expected output:

```
...
----------------------------------------------------------------------
Ran 3 tests in 5.618s

OK
```

Try to play with the XDP program in `program.c` and run the test suite again, what happens?
