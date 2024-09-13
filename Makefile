CC=afl-clang-lto
CXX=afl-clang-lto++

CC1=afl-clang-fast
CXX1=afl-clang-fast++

SYMCC=/root/Tools/symcc_build/symcc

all: asan cmplog compcov ctx ngram symcc
asan: main.c libncrx.c
        AFL_USE_ASAN=1 AFL_USE_UBSAN=1 $(CC) -o fuzz-asan main.c libncrx.c -I.
cmplog:
        AFL_LLVM_CMPLOG=1 $(CC) -o fuzz-cmplog main.c libncrx.c -I.
compcov:
        AFL_LLVM_LAF_ALL=1 $(CC) -o fuzz-compcov main.c libncrx.c -I.
ctx:
        AFL_LLVM_INSTRUMENT=CTX $(CC1) -o fuzz-ctx main.c libncrx.c -I.
ngram:
        AFL_LLVM_INSTRUMENT=NGRAM-8 $(CC1) -o fuzz-ngram main.c libncrx.c -I.
symcc:
        $(SYMCC) -o fuzz-symcc main_symcc.c libncrx.c -I.
coverage:
        gcc -fprofile-arcs -ftest-coverage -o fuzz-coverage main_symcc.c libncrx.c -I.
ubsan-gcc:
        gcc -fsanitize=undefined -g -O1 -fno-omit-frame-pointer -o fuzz-ubsan main_symcc.c libncrx.c -I.
klee:
        wllvm  -O0 -Xclang -disable-O0-optnone -o fuzzme_klee main_klee.c libncrx.c -L/home/klee/klee_build/lib -lkleeRuntest -I. -I/home/klee/klee_build/include -D__NO_STRING_INLINES -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__
