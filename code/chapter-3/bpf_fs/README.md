
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



## 学习记录

  本来准备使用书上的用法，在用户空间创建map，内核一起更改，但是一直没找到内核怎么使用用户空间创建的map，如果反过来就很轻易使用。
    stackoverflow有相似问题，但是看不到最终结论
    
        https://stackoverflow.com/questions/57628432/ebpf-maps-for-one-element-map-type-and-kernel-user-space-communication
	
	

   查了下calico的源码，发现这部分还是内核来初始化map，
   
   控制面(用户空间)利用bpftool repin 这些map，
   
   如果pin文件还在则通过文件找到对应的map的fd来操作，
   
   如果文件都不在了，则找对应的map来repin，同时获得fd。
   
   这里有个疑惑，如果内核态的重新加载，则会还会出来同名的map，但是map id不一样，与之前pin的持久化的map已经不是同一个map了（bpftool map list -j）,
   
   而之前的bpf fs文件不删除文件存在则会读取该pin的fd，这样用户态在用老的map，而内核在更新新的map，这块calico还没看到怎么处理的，
   
   按照我的想法是会去删除这个pin文件.
   
   查阅bpf samples，发现xdp的一个demo就是这么玩的：
   
   
   https://github.com/netoptimizer/prototype-kernel/blob/master/kernel/samples/bpf/xdp_ddos01_blacklist_user.c#L78
   
   目前觉得clico可能就是这样。。
   
   
   https://prototype-kernel.readthedocs.io/en/latest/bpf/ebpf_maps.html#export-map-to-filesystem
   
   也主要讲是在usernamespace共享map，没说内核态共享：
```
When Interacting with maps from Userspace a file descriptor is needed. 
There are two methods for sharing this file descriptor.

By passing it over Unix-domain sockets.
Exporting the map to a special bpf filesystem.
Option 2, exporting or pinning the map through the filesystem is more convenient and easier than option 1. 
Thus, this document will focus on option 2.

Todo

Describe the API for bpf_obj_pin and bpf_obj_get. 
Usage examples available in XDP blacklist for bpf_obj_pin() and XDP blacklist cmdline tool show use of bpf_obj_get().

Todo

add link to Daniel’s TC example of using Unix-domain sockets.

```

	新发现：
            可以用bpftool prog load 到内核时，通过指定pin好的map来替换内核程序初始化的映射名！
            例如：
                bpftool prog load lcm_map_pinning_save_kern.o /sys/fs/bpf/lcm_map_pinning_save  map name lcmdataset /sys/fs/bpf/lcm/my_dataset 
  
未来可以看看bpftool源码研究下。 
