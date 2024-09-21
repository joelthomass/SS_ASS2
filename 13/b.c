#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;
    printf("Enter the PID of the program to send SIGSTOP to: ");
    scanf("%d", &pid);

    if (kill(pid, SIGSTOP) == 0) {
        printf("SIGSTOP sent to process %d\n", pid);
    } else {
        perror("Failed to send SIGSTOP");
    }

    return 0;
}
