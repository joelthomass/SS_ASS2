#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char *message_to_send = "Hello from Program 1!";
    char buffer[100];

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Write to FIFO1
    int fd1 = open(FIFO1, O_WRONLY);
    write(fd1, message_to_send, sizeof(message_to_send));
    close(fd1);
    printf("Program 1 sent message: %s\n", message_to_send);

    // Read from FIFO2
    int fd2 = open(FIFO2, O_RDONLY);
    read(fd2, buffer, sizeof(buffer));
    close(fd2);
    printf("Program 1 received message: %s\n", buffer);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/21$ gcc -o 21a 21a.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/21$ gcc -o 21b 21b.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/21$ ./21a
Program 1 sent message: Hello from Program 1!
Program 1 received message: Hello fr
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/21$ ./21b
Program 2 received message: Hello fr
Program 2 sent message: Hello from Program 2!
*/
