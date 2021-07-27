#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "cacheutils.h"

int main() {
    /* Calibrate Flush+Reload */
    size_t cache_miss = calibrate_flush_reload();
    printf("[+] Cache miss threshold: %zd\n", cache_miss);

    /* Use file as shared memory */
    int fd = open("transfer", O_RDONLY);
    char* channel = (char*)mmap(0, 4096 * 256, PROT_READ, MAP_SHARED, fd, 0);

    /* Flush all pages from cache */
    for(int i = 0; i < 256; i++) {
        flush(channel + i * 4096);
    }

    unsigned char last_char = 0;

    while(1) {
        /* For every printable character in a pseudo-random order (to prevent prefetching effects) */
        for(int i = 0; i < 256; i++) {
            int character = (i * 101 + 17) % 256;
            if(character < 30 || character > 127) continue;
            /* TODO: Test if corresponding page is cached, if so output the corresponding key */
        }
    }

}
