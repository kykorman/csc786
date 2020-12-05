#!/usr/bin/env bash
set -eux
gcc -L /libc232/glibc/build/install/lib -I /libc232/glibc/build/install/include -Wl,--rpath=/libc232/glibc/build/install/lib -Wl,--dynamic-linker=/libc232/glibc/build/install/lib/ld-linux-x86-64.so.2 -std=c11 -o 2.32.out test.c
./2.32.out 10000000
