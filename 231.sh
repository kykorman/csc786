#!/usr/bin/env bash
set -eux
gcc -L /libc231/glibc/build/install/lib -I /libc231/glibc/build/install/include -Wl,--rpath=/libc231/glibc/build/install/lib -Wl,--dynamic-linker=/libc231/glibc/build/install/lib/ld-linux-x86-64.so.2 -std=c11 -o 2.31.out test.c
./2.31.out 10000000
