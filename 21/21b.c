#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char *message_to_send = "Hello from Program 2!";
    char buffer[100];

    // Read from FIFO1
    int fd1 = open(FIFO1, O_RDONLY);
    read(fd1, buffer, sizeof(buffer));
    close(fd1);
    printf("Program 2 received message: %s\n", buffer);

    // Write to FIFO2
    int fd2 = open(FIFO2, O_WRONLY);
    write(fd2, message_to_send, sizeof(message_to_send));
    close(fd2);
    printf("Program 2 sent message: %s\n", message_to_send);

    return 0;
}
