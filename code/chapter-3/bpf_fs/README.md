# Chapter 3: Pinning Maps to BPF Virtual File System

- A full description of this example can be found in Chapter 3.
- Please remember that the examples here are tested in the Vagrant machine. Please read more in [README.md](/README.md).
- Make sure to change the `Makefile` accordingly if you wish to build somewhere else, open an issue if you have problems doing so!
- All the dependencies are already handled if you followed the instructions in the main [README.md](/README.md).

**IMPORTANT NOTE**: If you find differences between what you have here and the copy you own, read [this](#differences-with-the-book-copy-you-have)

## Let's do it!

In the environment:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-3/bpf_fs
```

Compile the program and the loader

```bash
make bpfpin
```

It will create two BPF ELFs named `map_pinning_save.o` and `map_pinning_fetch.o` and their respective Loaders named `map-pin` and `map-read`.

Now you can execute the bpf programs with root privileges.

```
# ./map-pin
```

Verify the Map has been created in the BPF Virtual Filesystem.

```bash
# ls /sys/fs/bpf
```

If the program has been successful, you should see `my_array` present in the Virtual Filesystem.

Now, we can read from the pinned map.

```bash
# ./map-read
```

## Differences with the Book copy you have
The build procedure and code in this example can differ from the actual copy of the book you have.
We are updating the book so that future prints and PDFs are updated but your copy might be different.

**What is different?**
- This examples uses a `Makefile` to build the content that is only presented as source code in the book;
- Loaders are added for the examples;