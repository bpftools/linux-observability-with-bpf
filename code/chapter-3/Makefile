CLANG = clang
CC = gcc

BPFCODE = bpf_program
BPFTOOLS = /kernel-src/samples/bpf

CCINCLUDE += -I/kernel-src/tools/testing/selftests/bpf
# for bpf_load.h
CCINCLUDE += -I/kernel-src/samples/bpf
# for bpf/bpf.h
CCINCLUDE += -I/kernel-src/tools/lib
# for libbpf.h
CCINCLUDE += -I/kernel-src/tools/lib/bpf
LIBRARY_PATH = -L/urs/local/lib64/
BPFSO = -lbpf
ELFSO = -lelf

.PHONY: clean $(CLANG) bpfload build

clean:
	rm -f *.o *.so $(BPFCODE)

build: $(BPFCODE:=.c)
	$(CC) $(BPFCODE:=.c) $(CCINCLUDE) $(LIBRARY_PATH) $(BPFSO) $(ELFSO) -o $(BPFCODE)

execable: build
	@chmod +x $(BPFCODE)

#test: execable
#	FILEEXISTS="$(sudo file /sys/fs/bpf/my_array )"; echo $$FILEEXISTS

.DEFAULT_GOAL := execable
