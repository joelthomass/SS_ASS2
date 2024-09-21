#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSTOP, &sa, NULL);

    printf("Waiting to catch SIGSTOP (PID = %d)\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/13$ gcc -o b b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/13$ ./a &
[1] 8894
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/13$ Waiting to catch SIGSTOP (PID = 8894)
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/13$ ./b
Enter the PID of the program to send SIGSTOP to: 8894
SIGSTOP sent to process 8894
*/
