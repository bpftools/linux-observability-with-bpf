/* Copyright (c) 2016 Facebook
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#define KBUILD_MODNAME "foo"
#include <uapi/linux/bpf.h>
#include <uapi/linux/if_ether.h>
#include <uapi/linux/if_packet.h>
#include <uapi/linux/ip.h>
#include <uapi/linux/ipv6.h>
#include <uapi/linux/in.h>
#include <uapi/linux/tcp.h>
#include <uapi/linux/filter.h>
#include <uapi/linux/pkt_cls.h>
#include <net/ipv6.h>
#include "bpf_helpers.h"

#define _htonl __builtin_bswap32

#define PIN_GLOBAL_NS		2
struct bpf_elf_map {
	__u32 type;
	__u32 size_key;
	__u32 size_value;
	__u32 max_elem;
	__u32 flags;
	__u32 id;
	__u32 pinning;
};

/* copy of 'struct ethhdr' without __packed */
struct eth_hdr {
	unsigned char   h_dest[ETH_ALEN];
	unsigned char   h_source[ETH_ALEN];
	unsigned short  h_proto;
};

struct bpf_elf_map SEC("maps") counter_map = {
	.type = BPF_MAP_TYPE_ARRAY,
	.size_key = sizeof(int),
	.size_value = sizeof(int),
	.pinning = PIN_GLOBAL_NS,
	.max_elem = 256,
};


static inline int is_http(struct __sk_buff *skb, __u64 nh_off);
SEC("classifier")
int classification(struct __sk_buff *skb)
{
	void *data = (void *)(long)skb->data;
	struct eth_hdr *eth = data;
	void *data_end = (void *)(long)skb->data_end;
	int key = 0, *el;
        int one = 1;
     __u64 nh_off = 0;
  nh_off = sizeof(*eth);

	if (data + sizeof(*eth) > data_end)
		return TC_ACT_OK;
        key =   eth->h_proto;
	el = bpf_map_lookup_elem(&counter_map, &key);
if(el){
 (*el)++;
}
else{
  el = &one;
}
      bpf_map_update_elem(&counter_map, &key, el, BPF_ANY);
  char msg[] = "Hello, BPF World!";
  bpf_trace_printk(msg, sizeof(msg));

  if (key == htons(ETH_P_IP)) {
    if (is_http(skb, nh_off) == 1) {
        char msg1[] = "HTTP!!!!!";
        bpf_trace_printk(msg, sizeof(msg1));
    }
  }


	return TC_ACT_OK;
}


static inline int is_http(struct __sk_buff *skb, __u64 nh_off) {
  void *data_end = (void *)(long)skb->data_end;
  void *data = (void *)(long)skb->data;
  struct iphdr *iph = data + nh_off;

  if (iph + 1 > data_end) {
    return 0;
  }

  if (iph->protocol != IPPROTO_TCP) {
    return 0;
  }
  __u32 tcp_hlen = 0;
  __u32 ip_hlen = 0;
  __u32 poffset = 0;
  __u32 plength = 0;
  __u32 ip_total_length = iph->tot_len;

  ip_hlen = iph->ihl << 2;

  if (ip_hlen < sizeof(*iph)) {
    return 0;
  }

  struct tcphdr *tcph = data + nh_off + sizeof(*iph);

  if (tcph + 1 > data_end) {
    return 0;
  }

  tcp_hlen = tcph->doff << 2;

  poffset = ETH_HLEN + ip_hlen + tcp_hlen;
  plength = ip_total_length - ip_hlen - tcp_hlen;
  if (plength >= 7) {
    unsigned long p[7];
    int i = 0;
    for (i = 0; i < 7; i++) {

      p[i] = load_byte(skb, poffset + i);
    }
    int *value;
    if ((p[0] == 'H') && (p[1] == 'T') && (p[2] == 'T') && (p[3] == 'P')) {
      return 1;
    }
  }

  return 0;
}

char _license[] SEC("license") = "GPL";
