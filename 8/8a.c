#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV: Segmentation Fault\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, sigsegv_handler);
    
    int *p = NULL;
    *p = 42;

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ gcc -o 8a 8a.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/8$ ./8a
Caught SIGSEGV: Segmentation Fault
*/
