#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Get the maximum number of open files
    long max_open_files = sysconf(_SC_OPEN_MAX);
    if (max_open_files == -1) {
        perror("sysconf failed for _SC_OPEN_MAX");
        return 1;
    }
    printf("Maximum number of files that can be opened: %ld\n", max_open_files);

    // Create a pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Calculate pipe buffer size by filling the pipe
    long pipe_size = 0;
    char data = 'A';
    while (write(pipefd[1], &data, 1) != -1) {
        pipe_size++;
    }

    if (errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("write failed");
    }
    printf("Size of the pipe's circular buffer: %ld bytes\n", pipe_size);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/23$ gcc -o 23 23.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/23$ ./23
Maximum number of files that can be opened: 1024
*/
