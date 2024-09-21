#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void timer_handler(int signum) {
    printf("ITIMER_VIRTUAL timer expired!\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    while (1);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/1$ gcc -o 1b 1b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/1$ ./1b
ITIMER_VIRTUAL timer expired!
ITIMER_VIRTUAL timer expired!
*/
