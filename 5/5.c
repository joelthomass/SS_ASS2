#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>

int main() {
    long arg_max = sysconf(_SC_ARG_MAX);
    printf("Maximum length of the arguments to exec family: %ld\n", arg_max);

    long max_procs = sysconf(_SC_CHILD_MAX);
    printf("Maximum number of simultaneous processes per user ID: %ld\n", max_procs);

    long clock_ticks = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks per second: %ld\n", clock_ticks);

    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE, &rl);
    printf("Maximum number of open files: %lu\n", rl.rlim_cur);

    long page_size = sysconf(_SC_PAGESIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    long total_pages = sysconf(_SC_PHYS_PAGES);
    printf("Total number of pages in physical memory: %ld\n", total_pages);

    long avail_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("Number of currently available pages in physical memory: %ld\n", avail_pages);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/5$ gcc -o 5 5.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/5$ ./5
Maximum length of the arguments to exec family: 2097152
Maximum number of simultaneous processes per user ID: 28884
Number of clock ticks per second: 100
Maximum number of open files: 1024
Size of a page: 4096 bytes
Total number of pages in physical memory: 1867338
Number of currently available pages in physical memory: 976798
*/
