#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        dup(pipefd[1]);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    } else {  // Parent process (wc)
        close(pipefd[1]);
        dup(pipefd[0]);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/17$ gcc -o 17a 17a.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/17$ ./17a
total 20
-rwxrwxr-x 1 joelthomas joelthomas 16208 Sep 21 13:59 17a
-rw-rw-r-- 1 joelthomas joelthomas   718 Sep 21 13:58 17a.c
*/
