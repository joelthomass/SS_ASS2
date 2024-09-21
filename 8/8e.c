#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h> 
void sigalrm_handler(int signum) {
    printf("Caught SIGALRM\n");
}

int main() {
    struct itimerval timer;

    signal(SIGALRM, sigalrm_handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    pause(); 

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8e 8e.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8e
Caught SIGALRM
*/
