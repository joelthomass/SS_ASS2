#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void sigvtalrm_handler(int signum) {
    printf("Caught SIGVTALRM\n");
}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, sigvtalrm_handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    while (1);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8f 8f.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8f
Caught SIGVTALRM
*/
