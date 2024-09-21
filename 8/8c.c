#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE: Floating-Point Exception\n");
    exit(1);
}

int main() {
    signal(SIGFPE, sigfpe_handler);
    
    int a = 1;
    int b = 0;
    int c = a / b;  // Trigger a division by zero

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8c 8c.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8c
Caught SIGFPE: Floating-Point Exception
*/
