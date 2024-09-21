#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_name = "myfifo";
    int fd;
    char *message = "Hello from writer!";

    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo failed");
    }

    fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }

    write(fd, message, sizeof(message));
    close(fd);

    printf("Writer sent message: %s\n", message);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/20$ gcc -o 20a 20a.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/20$ gcc -o 20b 20b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/20$ ./20a
Writer sent message: Hello from writer!
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/20$ ./20b
Reader received message: Hello fr
*/
