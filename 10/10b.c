#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT: Interrupt signal\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    while (1) {
        printf("Running... Press Ctrl+C to trigger SIGINT\n");
        sleep(1);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ gcc -o 10b 10b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/10$ ./10b
Running... Press Ctrl+C to trigger SIGINT
Running... Press Ctrl+C to trigger SIGINT
Running... Press Ctrl+C to trigger SIGINT
^CCaught SIGINT: Interrupt signal
*/
