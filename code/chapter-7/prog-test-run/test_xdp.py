from bcc import BPF, libbcc
from scapy.all import Ether, IP, raw, TCP, UDP

import ctypes
import unittest


class XDPExampleTestCase(unittest.TestCase):
    SKB_OUT_SIZE = 1514  # mtu 1500 + 14 ethernet size
    bpf_function = None

    def _xdp_test_run(self, given_packet, expected_packet, expected_return):
        size = len(given_packet)

        given_packet = ctypes.create_string_buffer(raw(given_packet), size)
        packet_output = ctypes.create_string_buffer(self.SKB_OUT_SIZE)

        packet_output_size = ctypes.c_uint32()
        test_retval = ctypes.c_uint32()
        duration = ctypes.c_uint32()
        repeat = 1
        ret = libbcc.lib.bpf_prog_test_run(self.bpf_function.fd,
                                           repeat,
                                           ctypes.byref(given_packet),
                                           size,
                                           ctypes.byref(packet_output),
                                           ctypes.byref(packet_output_size),
                                           ctypes.byref(test_retval),
                                           ctypes.byref(duration))
        self.assertEqual(ret, 0)
        self.assertEqual(test_retval.value, expected_return)

        if expected_packet:
            self.assertEqual(
                packet_output[:packet_output_size.value], raw(expected_packet))

    def setUp(self):
        bpf_prog = BPF(src_file=b"program.c")
        self.bpf_function = bpf_prog.load_func(b"myprogram", BPF.XDP)

    def test_drop_tcp(self):
        given_packet = Ether() / IP() / TCP()
        self._xdp_test_run(given_packet, None, BPF.XDP_DROP)

    def test_pass_udp(self):
        given_packet = Ether() / IP() / UDP()
        expected_packet = Ether() / IP() / UDP()
        self._xdp_test_run(given_packet, expected_packet, BPF.XDP_PASS)

    def test_transform_dst(self):
        given_packet = Ether() / IP() / TCP(dport=9090)
        expected_packet = Ether(dst='08:00:27:dd:38:2a') / \
            IP() / TCP(dport=9090)
        self._xdp_test_run(given_packet, expected_packet, BPF.XDP_TX)


if __name__ == '__main__':
    unittest.main()
