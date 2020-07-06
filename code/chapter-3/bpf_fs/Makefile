CLANG = clang

READEXECABLE = map-read
PINEXECABLE = map-pin

READBPFCODE = map_pinning_fetch
PINBPFCODE = map_pinning_save

BPFTOOLS = /kernel-src/samples/bpf
BPFLOADER = $(BPFTOOLS)/bpf_load.c

INCLUDE += -I/kernel-src/samples/bpf
INCLUDE += -I/kernel-src/tools/lib

CCINCLUDE += -I/kernel-src/tools/testing/selftests/bpf
CCINCLUDE += -I/kernel-src/tools/lib/bpf
CCINCLUDE += ${INCLUDE}

LOADINCLUDE += -I/kernel-src/tools/include
LOADINCLUDE += -I/kernel-src/tools/perf
LOADINCLUDE += ${INCLUDE}
LIBRARY_PATH = -L/usr/local/lib64
BPFSO = -lbpf

.PHONY: clean bpfload build

clean:
	rm -f *.o *.so map-*

build: ${BPFCODE.c} ${BPFLOADER}
	$(CLANG) -O2 -target bpf -c $(READBPFCODE:=.c) $(CCINCLUDE) -o ${READBPFCODE:=.o} && \
		$(CLANG) -O2 -target bpf -c $(PINBPFCODE:=.c) $(CCINCLUDE) -o ${PINBPFCODE:=.o}

bpfpin: build
	clang -o $(PINEXECABLE) -lelf $(LOADINCLUDE) $(LIBRARY_PATH) $(BPFSO) \
        $(BPFLOADER) pin_loader.c && \
        clang -o $(READEXECABLE) -lelf $(LOADINCLUDE) $(LIBRARY_PATH) $(BPFSO) \
                $(BPFLOADER) read_loader.c

.DEFAULT_GOAL := bpfload
