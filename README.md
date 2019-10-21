<p><img align="right" src="/img/owl.png" width="150px"/></p>
<p></p>

# Linux Observability with BPF code examples

This is the companion code repo for the book [Linux Observability with BPF](http://shop.oreilly.com/product/0636920242581.do).

We believe that even if the examples included in the book were all tested and working when we wrote them, human error is possible and technology changes.
For that reason, the purpose of this repo is to keep them as updated as possible and correct mistakes we made while writing the book.


## Code examples

### Chapter 6 - Linux Networking and BPF

- [Packet filtering for raw sockets](/code/chapter-6/packet-filtering-raw-sockets)
- [Traffic control classifier program using cls_bpf](/code/chapter-6/tc-flow-bpf-cls)

### Chapter 7 - eXpress Data Path (XDP)

- [XDP using iproute2 as a loader](/code/chapter-7/iproute2)
- [XDP using BCC as a loader](/code/chapter-7/bcc)
- [Testing XDP programs](/code/chapter-7/prog-test-run)


### Chapter 8 - Linux Kernel security, Capabilities and Seccomp

- [Seccomp BPF filter example](/code/chapter-8/seccomp)
