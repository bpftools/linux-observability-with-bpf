# Chapter 8: Linux Kernel security, Capabilities and Seccomp

- A full description of this example can be found in Chapter 8. It explains the various steps better and walks you trough the code here.
- Please remember that the examples here are tested in the Vagrant machine. Please read more in [README.md](/README.md).
- Make sure to change the example accordingly if you wish to build somewhere else, open an issue if you have problems doing so!
- All the dependencies are already handled if you followed the instructions in the main [README.md](/README.md).


In the machine:

Enter into this example folder:

```bash
cd ~/linux-observability-with-bpf/code/chapter-8/seccomp
```


Compiling this program is very straightforward, you just do a:


```bash
clang main.c -o filter-write
```

The program is made to filter any write syscall that happens, if you try it using a command that is supposed
to write it will not print anything.


Let's first do a command that prints stuff, like `ls -la`:

```bash
[vagrant@bpfbook seccomp]$ ls -la
total 40
drwxr-xr-x. 2 vagrant vagrant  4096 Dec 10 01:07 .
drwxr-xr-x. 3 vagrant vagrant  4096 Oct 29 16:59 ..
-rwxrwxr-x. 1 vagrant vagrant 22016 Dec 10 01:07 filter-write
-rw-r--r--. 1 vagrant vagrant    19 Oct 29 16:59 .gitignore
-rw-r--r--. 1 vagrant vagrant  1210 Oct 29 16:59 main.c
```

Now let's do the same with `filter-write`:

```
[vagrant@bpfbook seccomp]$ ./filter-write "ls -la"
```

No output! Let's see why!

We can use `strace` to dig into this:

```bash
strace -f ./filter-write "ls -la"
[pid  2657] lstat(".gitignore", {st_mode=S_IFREG|0644, st_size=19, ...}) = 0
[pid  2657] lgetxattr(".gitignore", "security.selinux", "unconfined_u:object_r:default_t:"..., 255) = 35
[pid  2657] getxattr(".gitignore", "system.posix_acl_access", NULL, 0) = -1 ENODATA (No data available)
[pid  2657] getdents64(3, /* 0 entries */, 32768) = 0
[pid  2657] close(3)                    = 0
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en_US.UTF-8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en_US.utf8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en_US/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en.UTF-8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en.utf8/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
[pid  2657] openat(AT_FDCWD, "/usr/share/locale/en/LC_MESSAGES/coreutils.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
```

All the write syscalls got `ENOENT` as defined in `main.c`, that's why no output was given!



