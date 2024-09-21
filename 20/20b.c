#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_name = "myfifo";
    int fd;
    char buffer[100];

    fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader received message: %s\n", buffer);
    close(fd);

    return 0;
}
