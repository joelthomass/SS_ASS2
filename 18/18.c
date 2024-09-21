#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid1, pid2;

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {  // First child process (ls -l)
        close(pipefd1[0]);
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    } else {
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid2 == 0) {  // Second child process (grep ^d)
            close(pipefd1[1]);
            dup2(pipefd1[0], STDIN_FILENO);
            close(pipefd1[0]);

            close(pipefd2[0]);
            dup2(pipefd2[1], STDOUT_FILENO);
            close(pipefd2[1]);

            execlp("grep", "grep", "^d", NULL);
            perror("execlp failed");
            exit(1);
        } else {  // Parent process (wc -l)
            close(pipefd1[0]);
            close(pipefd1[1]);

            close(pipefd2[1]);
            dup2(pipefd2[0], STDIN_FILENO);
            close(pipefd2[0]);

            execlp("wc", "wc", "-l", NULL);
            perror("execlp failed");
            exit(1);
        }
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/18$ gcc -o 18 18.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/18$ ./18
0
*/
