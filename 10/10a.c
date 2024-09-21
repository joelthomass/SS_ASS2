#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV: Segmentation Fault\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    *p = 42;

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ gcc -o 10a 10a.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ ./10a
Caught SIGSEGV: Segmentation Fault
*/
