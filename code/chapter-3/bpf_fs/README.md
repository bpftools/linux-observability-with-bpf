
## first make the dir and mount bpf

```shell

mount -t bpf /sys/fs/bpf /sys/fs/bpf
mkdir /sys/fs/bpf/lcm

```


## reference

calico:
	https://docs.projectcalico.org/maintenance/ebpf/enabling-bpf
	(calico bpf 内核部分)https://github.com/projectcalico/felix/tree/master/bpf-gpl
	(calico bpf golang控制面部分)https://github.com/projectcalico/felix/tree/master/bpf

	本来准备使用书上的用法，在用户空间创建map，内核一起更改，但是一直没找到内核怎么使用用户空间创建的map，如果反过来就很轻易使用。
        stackoverflow有相似问题，但是看不到最终结论
            https://stackoverflow.com/questions/57628432/ebpf-maps-for-one-element-map-type-and-kernel-user-space-communication

        最终查了下calico的源码，发现这部分还是内核来初始化map，控制面(用户空间)利用bpftool repin 这些map，如果pin文件还在则通过文件找到对应的map的fd来操作，如果文件都不在了，则找对应的map来repin，同时获得fd。

