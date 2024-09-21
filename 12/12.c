#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent process: PID = %d\n", getpid());
        sleep(5);
    } 
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        printf("Child process sending SIGKILL to parent (PID = %d)\n", getppid());
        kill(getppid(), SIGKILL);
        sleep(10);
        printf("Child process exiting. It is now an orphan.\n");
    } 
    else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/12$ gcc -o 12 12.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/12$ ./12
Parent process: PID = 8332
Child process: PID = 8333
Child process sending SIGKILL to parent (PID = 8332)
Killed
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/12$ Child process exiting. It is now an orphan.
^C
*/
