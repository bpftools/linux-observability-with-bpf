#include <arpa/inet.h>
#include <assert.h>
#include <bpf/bpf.h>
#include <bpf/bpf_load.h>
#include <bpf/sock_example.h>
#include <errno.h>
#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

char bpf_log_buf[BPF_LOG_BUF_SIZE];

int main(int argc, char **argv) {
  int sock = -1, i, key;
  int tcp_cnt, udp_cnt, icmp_cnt;

  char filename[256];
  snprintf(filename, sizeof(filename), "%s", argv[1]);

  if (load_bpf_file(filename)) {
    printf("%s", bpf_log_buf);
    return 1;
  }

  sock = open_raw_sock("lo");

  if (setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, prog_fd,
                 sizeof(prog_fd[0]))) {
    printf("setsockopt %s\n", strerror(errno));
    return 0;
  }

  for (i = 0; i < 10; i++) {
    key = IPPROTO_TCP;
    assert(bpf_map_lookup_elem(map_fd[0], &key, &tcp_cnt) == 0);

    key = IPPROTO_UDP;
    assert(bpf_map_lookup_elem(map_fd[0], &key, &udp_cnt) == 0);

    key = IPPROTO_ICMP;
    assert(bpf_map_lookup_elem(map_fd[0], &key, &icmp_cnt) == 0);

    printf("TCP %d UDP %d ICMP %d packets\n", tcp_cnt, udp_cnt, icmp_cnt);
    sleep(1);
  }
}
