<p><img align="right" src="/img/owl.png" width="150px"/></p>
<p></p>

# Linux Observability with BPF code examples

This is the companion code repo for the book [Linux Observability with BPF](https://bit.ly/bpf-safari).

We believe that even if the examples included in the book were all tested and working when we wrote them, human error is possible and technology changes.
For that reason, the purpose of this repo is to keep them as updated as possible and correct mistakes we made while writing the book.

**Nota Bene**: All the examples in this repository are adapted from the book to assume that you use the Vagrant environment we provide.
Examples can be slightly different in this repository because of that. The reason is that we didn't want to couple the book itself to Vagrant as a tool.
If you don't want a Vagrant based environment, make sure you have: [bcc](https://github.com/iovisor/bcc/blob/master/INSTALL.md) and [clang](https://clang.llvm.org/)


## Environment setup

- Please expand the details of the environment you want to work on.
- Remember that the examples have been tested on the Vagrant based environment primarily.
- Feel free to open an issue or a PR if you want to help in making this better for everyone!

<details>
<summary>Fedora 30</summary>

First, we need to install some build dependencies and all the tools needed for the examples:

```bash
sudo dnf install make glibc-devel.i686 elfutils-libelf-devel wget tar clang bcc strace kernel-devel -y
```

Then we need grab a copy of the source code of the current kernel.

In our case the kernel runing can be verified with `uname`.

```bash
$ uname -r
5.0.9-301.fc30.x86_64
```

Given that version, please notice the URL we fetch the sources from in the following command.
Change it according to your version.

```bash
cd /tmp
wget -c https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.0.9.tar.gz -O - | tar -xz
```

Now that we have the kernel source, we can move it to the `/kernel-src` folder.

**NOTE THAT: All the examples** using kernel sources in this repo assume that the kernel sources are available there. In case you don't like it,
make sure you do a search and replace!

At this point we move the kernel sources and compile `libbpf`. Again please notice the `5.0.9` here and change accordingly.

```
sudo mv linux-5.0.9 /kernel-src
cd /kernel-src/tools/lib/bpf
sudo make && sudo make install prefix=/
```

</details>

<details>
<summary>Ubuntu 18.04</summary>

First, we need to install some build dependencies and all the tools needed for the examples:

```bash
sudo apt update
sudo apt install build-essential git make libelf-dev clang strace tar bpfcc-tools linux-headers-$(uname -r) gcc-multilib
```

**Note on Kernel version**: make sure to have a recent kernel to run the examples, a version `>=5.0.0` will do the job. Most Ubuntu `18.04` providers are shipping with the kernel `4.15` that doesn't work for most of the examples. Upgrading options are left to the reader, we've been successful on aws by installing the `linux-image-5.0.0-1019-aws` package.

After dependencies, we need grab a copy of the kernel source code for the current release.
Since this assumes that you are running an updated Ubuntu 18.04 we can get it directly from the repo they provide.

```
cd /tmp
git clone --depth 1 git://kernel.ubuntu.com/ubuntu/ubuntu-bionic.git
```

Now that we have the kernel source, we can move it to the `/kernel-src` folder.

**NOTE THAT: All the examples** using kernel sources in this repo assume that the kernel sources are available at `/kernel-src`. In case you don't like it,
make sure you do a search and replace!


At this point we move the kernel sources and compile `libbpf`.

```
sudo mv ubuntu-bionic /kernel-src
cd /kernel-src/tools/lib/bpf
sudo make && sudo make install prefix=/usr/local
```

Ubuntu doesn't have the library path that the makefile expects so we need to move our libraries
to its library path now.

```
sudo mv /usr/local/lib64/libbpf.* /lib/x86_64-linux-gnu/
```

</details>

<details>
<summary>Vagrant (recommended)</summary>
We provide reproducible environment in the form of a Vagrantfile that installs all the needed to make the examples work.

The environment is based on Fedora 30.

### Install Vagrant

To install Vagrant, follow the official guide [here](https://www.vagrantup.com/docs/installation/).

Once you have Vagrant installed, you will need to clone this repository and issue a `vagrant up`.

```bash
git clone https://github.com/bpftools/linux-observability-with-bpf.git
cd linux-observability-with-bpf
vagrant up
```

This Vagrant command, will start a Fedora 30 VM in Virtualbox, you can SSH into the machine using:

```
vagrant ssh
```

Before going on, make sure you download the kernel source tree in this repository. It is needed as a dependency for some examples.
We will be downloading the code for Kernel 5.0.9 - We are avoiding a git clone here because the Git history of the kernel is very big.

In the machine:

```bash
cd /tmp
wget -c https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.0.9.tar.gz -O - | tar -xz
sudo mv linux-5.0.9 /kernel-src
```

At this point, we need to compile the `libbpf` library:

```
cd /kernel-src/tools/lib/bpf
make && sudo make install prefix=/
```


</details>


Before going to the examples, it will be useful to have a copy of this repo in your environment.

```
git clone https://github.com/bpftools/linux-observability-with-bpf.git ~/linux-observability-with-bpf
```

**IMPORTANT NOTE**: The examples assume that you clone the repo in your home folder `~/linux-observability-with-bpf`, if you didn't do
please remember to change your commands!

Yay, at this point you have everything and can follow the following code examples.

## Code examples

Click on each example to follow the setup instructions.


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
- [Uprobes](/code/chapter-4/uprobes)
- [Uretprobes ](/code/chapter-4/uretprobes)

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

- [XDP and iproute2 as a loader](/code/chapter-7/iproute2)
- [XDP and BCC](/code/chapter-7/bcc)
- [Testing XDP programs](/code/chapter-7/prog-test-run)


### Chapter 8 - Linux Kernel security, Capabilities and Seccomp

- [Seccomp BPF filter example](/code/chapter-8/seccomp)
