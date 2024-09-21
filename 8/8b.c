#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>  // Include this for sleep()

void sigint_handler(int signum) {
    printf("Caught SIGINT: Interrupt signal\n");
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);

    while (1) {
        printf("Running... Press Ctrl+C to trigger SIGINT\n");
        sleep(1);  // Now properly declared
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8b 8b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8b
Running... Press Ctrl+C to trigger SIGINT
Running... Press Ctrl+C to trigger SIGINT
Running... Press Ctrl+C to trigger SIGINT
Running... Press Ctrl+C to trigger SIGINT
*/
