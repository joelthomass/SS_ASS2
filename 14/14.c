#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char write_msg[] = "Hello, this is a message from the pipe!";
    char read_msg[100];
    
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    write(fd[1], write_msg, strlen(write_msg) + 1);
    read(fd[0], read_msg, sizeof(read_msg));

    printf("Message read from pipe: %s\n", read_msg);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/14$ gcc -o 14 14.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/14$ ./14
Message read from pipe: Hello, this is a message from the pipe!
*/
