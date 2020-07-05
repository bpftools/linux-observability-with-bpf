#include <sys/sdt.h>

int main(int argc, char const *argv[]) {
    DTRACE_PROBE("hello-usdt", "probe-main");
    return 0;
}

