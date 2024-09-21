#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE: Floating-Point Exception\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigfpe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    int a = 1;
    int b = 0;
    int c = a / b;

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ gcc -o 10c 10c.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ ./10c
Caught SIGFPE: Floating-Point Exception
*/
