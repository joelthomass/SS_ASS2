#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct sigaction sa_ignore, sa_default;

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);

    printf("SIGINT is currently ignored. Press Ctrl+C to test (nothing will happen).\n");
    sleep(5);

    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sigaction(SIGINT, &sa_default, NULL);

    printf("SIGINT has been reset to default action. Press Ctrl+C to test (program will terminate).\n");
    sleep(5);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/11$ gcc -o 11 11.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/11$ ./11
SIGINT is currently ignored. Press Ctrl+C to test (nothing will happen).
^CSIGINT has been reset to default action. Press Ctrl+C to test (program will terminate).
^C
*/
