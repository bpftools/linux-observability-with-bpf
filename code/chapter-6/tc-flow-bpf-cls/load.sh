#!/bin/bash
IFNAME=$1
tc qdisc add dev $IFNAME handle 0: ingress
tc filter add dev $IFNAME ingress  bpf obj classifier.o flowid 0:
