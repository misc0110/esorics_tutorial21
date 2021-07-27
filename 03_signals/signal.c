#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf buf;

/* Enable a signal again */
static void unblock_signal(int signum __attribute__((__unused__))) {
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, signum);
  sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

/* TODO: Implement a signal handler
 *  1. Unblock the SIGSEGV signal
 *  2. 'Restore' the program state by performing a longjmp back
 */
void segfaulthandler(int signum) {
}

int can_access(void* address) {
  /* TODO: Save program state */
  *(volatile size_t *)(address);
  return 1;
}

int main() {
    /* TODO: Setup signal handler */
    printf("Accessible: &main:  %d\n", can_access(&main));
    printf("Accessible: NULL:   %d\n", can_access(NULL));
    printf("Accessible: Kernel: %d\n", can_access((void*)0xffffffff81000000ull));    

    return 0;
}
