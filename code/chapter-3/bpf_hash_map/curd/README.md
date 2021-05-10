 
#参考 https://davidlovezoe.club/wordpress/archives/988  bpf编译环境搭建
#https://blog.csdn.net/alex_yangchuansheng/article/details/108332511 BPF数据传递的桥梁——BPF Map

## for the bpf devlopment env
```shell

yum install bison flex
yum install openssl-devel  openssl


 cd ~/lcm/linux-source/linux-4.18  
make headers_install
 make oldconfig


cd samples/bpf/

make


#特别重要，否则会出现
#[root@superglk bpf]# ./lcm 
#failed to create a map: 1 Operation not permitted
#The kernel didn't load the BPF program


ulimit -l unlimited
```


为自己的BPF程序生成可执行文件
如果你想利用Linux内核环境来编译自己的BPF程序，
是非常方便的。
只要对samples/bpf/目录下的Makefile进行一点点自定义改造即可，

```shell


# 1. 追加新的一行至hostprogs-y开头的代码块最后，保证自己的BPF程序能够生成可执行文件

hostprogs-y += lcm
# 2. 一般BPF程序使用以下命令即可，具体取决于你的程序是否依赖其他特殊头文件
lcm-objs := bpf_load.o lcm_user.o


# 3. 追加新的一行至always开头的代码块最后，保证触发生成可执行文件的任务

always += lcm_kern.o


```



一般的BPF程序只需要通过如上3处更新加入到Makefile中，就可以使用make samples/bpf/命令，生成你自己程序的可执行文件了。





