#include <stdio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "cacheutils.h"


volatile unsigned char to_send;

void* input(void* dummy) {
    while(1) {
        printf("Enter character to send: ");
        int c = getchar();
        if(c >= 30 && c <= 127) {
            to_send = c;
            printf("\n");
        }
        if(c == EOF) exit(1);
    }
}

int main() {
    pthread_t input_thread;
    
    /* Use file as shared memory */
    int fd = open("transfer", O_RDONLY);
    char* channel = (char*)mmap(0, 4096 * 256, PROT_READ, MAP_SHARED, fd, 0);

    /* Force pages to be mapped */
    int i;
    for(i = 0; i < 256; i++) {
        maccess(channel + i * 4096);
    }
    
    /* Start input thread */
    pthread_create(&input_thread, NULL, input, NULL);
    
    /* Transmit character */
    while(1) {
        // TODO: access part of the shared memory file (channel) depending on the input
        //       the current character is stored in "to_send"
        usleep(100);
    }
}
