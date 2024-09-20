#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

void print_limit(int resource, const char* resource_name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%s limits:\n", resource_name);
        printf("  Soft limit: %ld\n", (long)limit.rlim_cur);
        printf("  Hard limit: %ld\n\n", (long)limit.rlim_max);
    } else {
        printf("Error retrieving %s limit: %s\n", resource_name, strerror(errno));
    }
}

int main() {
    print_limit(RLIMIT_CPU, "CPU Time");
    print_limit(RLIMIT_FSIZE, "File Size");
    print_limit(RLIMIT_DATA, "Data Segment Size");
    print_limit(RLIMIT_STACK, "Stack Size");
    print_limit(RLIMIT_CORE, "Core File Size");
    print_limit(RLIMIT_RSS, "Resident Set Size");
    print_limit(RLIMIT_NOFILE, "Number of Open Files");
    print_limit(RLIMIT_AS, "Address Space Size");
    print_limit(RLIMIT_NPROC, "Number of Processes");
    print_limit(RLIMIT_MEMLOCK, "Locked-in-Memory Size");
    print_limit(RLIMIT_LOCKS, "File Locks");

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/2$ gcc -o 2 2.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/2$ ./2
CPU Time limits:
  Soft limit: -1
  Hard limit: -1

File Size limits:
  Soft limit: -1
  Hard limit: -1

Data Segment Size limits:
  Soft limit: -1
  Hard limit: -1

Stack Size limits:
  Soft limit: 8388608
  Hard limit: -1

Core File Size limits:
  Soft limit: 0
  Hard limit: -1

Resident Set Size limits:
  Soft limit: -1
  Hard limit: -1

Number of Open Files limits:
  Soft limit: 1024
  Hard limit: 1048576

Address Space Size limits:
  Soft limit: -1
  Hard limit: -1

Number of Processes limits:
  Soft limit: 28884
  Hard limit: 28884

Locked-in-Memory Size limits:
  Soft limit: 956076032
  Hard limit: 956076032

File Locks limits:
  Soft limit: -1
  Hard limit: -1

*/
