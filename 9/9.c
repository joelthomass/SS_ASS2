#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT (this won't show when ignored)\n");
}

int main() {
    signal(SIGINT, SIG_IGN);
    printf("SIGINT is currently ignored. Press Ctrl+C to test.\n");

    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("SIGINT has been reset to default action. Press Ctrl+C to test.\n");

    sleep(5);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/9$ ./9
SIGINT is currently ignored. Press Ctrl+C to test.
^CSIGINT has been reset to default action. Press Ctrl+C to test.
^C
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/9$ 
*/
