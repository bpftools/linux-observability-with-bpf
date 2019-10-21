#!/bin/bash
IFNAME=$1
sudo tc qdisc del dev $IFNAME ingress
