#include <stdio.h>
#include <unistd.h>

unsigned long long rdtsc() {
    unsigned int lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start, end;
    int i;

    start = rdtsc();

    for (i = 0; i < 100; i++) {
        getppid();
    }

    end = rdtsc();

    printf("Time taken to execute 100 getppid() system calls: %llu clock cycles\n", end - start);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/4$ gcc -o 4 4.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/4$ ./4
Time taken to execute 100 getppid() system calls: 199462 clock cycles
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/4$ 
*/
