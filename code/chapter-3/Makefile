CLANG = clang

INCLUDE_PATH += -I/kernel-src/tools/lib/bpf

LIBRARY_PATH = -L/usr/local/lib64
BPFSO = -lbpf

.PHONY: clean 

clean:
	rm -f fetch bpf_fs/save

fetch: 	map_pinning_fetch.c 
	clang -o fetch -lelf $(INCLUDE_PATH) $(LIBRARY_PATH) $(BPFSO) $?

save: 	bpf_fs/map_pinning_save.c
	clang -o bpf_fs/save -lelf $(INCLUDE_PATH) $(LIBRARY_PATH) $(BPFSO) $?

build: fetch save

.DEFAULT_GOAL := build
