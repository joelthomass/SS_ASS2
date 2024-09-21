
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];
    int fd;
    fd_set readfds;
    struct timeval timeout;

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo failed");
        return 1;
    }

    fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        int result = select(fd + 1, &readfds, NULL, NULL, &timeout);

        if (result == -1) {
            perror("select failed");
            close(fd);
            return 1;
        } else if (result == 0) {
            printf("Timeout! No data written to FIFO in 10 seconds.\n");
            continue;
        } else {
            if (FD_ISSET(fd, &readfds)) {
                ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
                if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    printf("Received message: %s\n", buffer);
                } else if (bytesRead == 0) {
                    printf("FIFO closed by writer.\n");
                    break;
                } else {
                    perror("read failed");
                }
            }
        }
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/22$ gcc -o 22 22.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/22$ ./22
Timeout! No data written to FIFO in 10 seconds.
Timeout! No data written to FIFO in 10 seconds.
Received message: Hello, FIFO!

FIFO closed by writer.

joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/22$ echo "Hello, FIFO!" > myfifo
*/
