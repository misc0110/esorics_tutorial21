#ifndef _CACHEUTILS_H_
#define _CACHEUTILS_H_

#include <stdint.h>

uint64_t rdtsc() {
  uint64_t a, d = 0;

  asm volatile("mfence");
  asm volatile("rdtsc" : "=a"(a), "=d"(d));
  a = (d << 32) | a;
  asm volatile("mfence");

  return a;
}

void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

void maccess(void *p) {
  asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

#endif
