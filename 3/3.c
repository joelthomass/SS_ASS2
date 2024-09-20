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
        printf("Error\n");
    }
}

void set_limit(int resource, rlim_t new_limit) {
    struct rlimit limit;
    
    if (getrlimit(resource, &limit) != 0) {
        printf("Error\n");
        return;
    }

    limit.rlim_cur = new_limit;

    if (setrlimit(resource, &limit) != 0) {
        printf("Error\n");
    } else {
        printf("Successfully set new limit.\n");
    }
}

int main() {
    printf("Before\n");
    print_limit(RLIMIT_FSIZE, "File Size");

    printf("Setting size to 1KB\n");
    set_limit(RLIMIT_FSIZE, 1024);

    printf("After\n");
    print_limit(RLIMIT_FSIZE, "File Size");

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/3$ gcc -o 3 3.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/3$ ./3
Before
File Size limits:
  Soft limit: -1
  Hard limit: -1

Setting size to 1KB
Successfully set new limit.
After
File Size limits:
  Soft limit: 1024
  Hard limit: -1
*/
