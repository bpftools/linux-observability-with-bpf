CLANG = clang
CC = gcc

LINUXINCLUDE += -I

EXECABLE = monitor-exec

BPFCODE = bpf_program

BPFTOOLS = /kernel-src/samples/bpf
BPFLOADER = $(BPFTOOLS)/bpf_load.c

CCINCLUDE += -I/kernel-src/tools/testing/selftests/bpf

# for bpf_load.h
LOADINCLUDE += -I/kernel-src/samples/bpf
# for bpf/bpf.h
LOADINCLUDE += -I/kernel-src/tools/lib
# for libbpf.h
LOADINCLUDE += -I/kernel-src/tools/lib/bpf

LOADINCLUDE += -I/kernel-src/tools/perf
LOADINCLUDE += -I/kernel-src/tools/include
LIBRARY_PATH = -L/urs/local/lib64/
BPFSO = -lbpf
ELFSO = -lelf

.PHONY: clean $(CLANG) bpfload build

clean:
	rm -f *.o *.so $(BPFCODE)

build: ${BPFCODE.c}
	${CC} $(BPFCODE:=.c) -I/kernel-src/tools/testing/selftests/bpf -I/kernel-src/samples/bpf -I/kernel-src/tools/lib -I/kernel-src/tools/lib/bpf $(LIBRARY_PATH) $(BPFSO) $(ELFSO) -o $(BPFCODE)

execable: build
	chmod +x $(BPFCODE)

#test: execable
#	FILEEXISTS="$(sudo file /sys/fs/bpf/my_array )"; echo $$FILEEXISTS

.DEFAULT_GOAL := build
