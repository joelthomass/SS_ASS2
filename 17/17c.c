#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process (ls -l)
        close(pipefd[0]);
        fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    } else {  // Parent process (wc)
        close(pipefd[1]);
        fcntl(pipefd[0], F_DUPFD, STDIN_FILENO);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/17$ ./17c
total 60
-rwxrwxr-x 1 joelthomas joelthomas 16208 Sep 21 13:59 17a
-rw-rw-r-- 1 joelthomas joelthomas  1018 Sep 21 13:59 17a.c
-rwxrwxr-x 1 joelthomas joelthomas 16208 Sep 21 14:00 17b
-rw-rw-r-- 1 joelthomas joelthomas   946 Sep 21 14:01 17b.c
-rwxrwxr-x 1 joelthomas joelthomas 16208 Sep 21 14:03 17c
-rw-rw-r-- 1 joelthomas joelthomas   788 Sep 21 14:02 17c.c
*/
