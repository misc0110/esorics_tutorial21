#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/mman.h>
#include <signal.h>
#include <setjmp.h>
#include <fcntl.h>
#include "cacheutils.h"

#define FROM 'A'
#define TO 'Z'

char __attribute__((aligned(4096))) mem[4096 * 256];


static jmp_buf buf;

// Enable a signal again
static void unblock_signal(int signum __attribute__((__unused__))) {
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, signum);
  sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

// Signal handler unblocking the signal and "restoring" the program state
void segfaulthandler(int signum) {
    unblock_signal(SIGSEGV);
    longjmp(buf, 1);
}


int main(int argc, char *argv[]) {
  int hist[256];
  memset(hist, 0, sizeof(hist));
  memset(mem, 1, sizeof(mem));

  // Get a valid page and its direct physical map address (i.e., a kernel mapping to the page)
  char *mapping = (char *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE, -1, 0);
  memset(mapping, 'C', 4096);

  size_t paddr = get_physical_address((size_t)mapping);
  if (paddr < 4096) {
    printf("[!] Could not get physical address! Did you start as root?\n");
    exit(1);
  }
  char *target = (char *)(0xffff888000000000ull + paddr); // direct-physical-map address + physical address = kernel virtual address

  printf("[+] Kernel address: %p\n", target);

  // Calibrate cache hit/miss threshold
  size_t cache_miss = calibrate_flush_reload();
  fprintf(stderr, "[+] Flush+Reload Threshold: %zd\n", cache_miss);

  // Flush the "covert channel"
  for(int i = 0; i < 256; i++) {
      flush(mem + i * 4096);
  }

  // Setup signal handler
  signal(SIGSEGV, segfaulthandler);

  while (1) {
    // TODO: Ensure the kernel mapping refers to a value not in the cache

    // Not in cache -> reads load buffer entry
    // TODO: Read from the kernel mapping and encode the read value into the cache

    // Recover value from cache and update histogram
    int max = 0, hit = 0;
    for(int i = FROM; i <= TO; i++) {
        if(flush_reload(mem + i * 4096) < cache_miss) {
            hist[i]++;
            hit = 1;
        }

        if(hist[i] > max) max = hist[i];
    }

    // If new hit, display histogram
    if (hit) {
        printf("\x1b[2J");
        for (int i = FROM; i <= TO; i++) {
            printf("%c: (%4d) ", i, hist[i]);
            for (int j = 0; j < hist[i] * 60 / max; j++) {
                printf("#");
            }
            printf("\n");
        }
    }
  }


  return 0;
}
