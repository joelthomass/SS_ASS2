#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void sigprof_handler(int signum) {
    printf("Caught SIGPROF\n");
}

int main() {
    struct itimerval timer;

    signal(SIGPROF, sigprof_handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    while (1);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8g 8g.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8g
Caught SIGPROF
*/
