#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2], child_to_parent[2];
    pid_t pid;
    char parent_msg[] = "Hello from Parent!";
    char child_msg[] = "Hello from Child!";
    char read_msg[100];

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid > 0) {
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);
        close(parent_to_child[1]);

        read(child_to_parent[0], read_msg, sizeof(read_msg));
        printf("Parent received message: %s\n", read_msg);
        close(child_to_parent[0]);
    } 
    else {
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        read(parent_to_child[0], read_msg, sizeof(read_msg));
        printf("Child received message: %s\n", read_msg);
        close(parent_to_child[0]);

        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);
        close(child_to_parent[1]);
    }

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/16$ gcc -o 16 16.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/16$ ./16
Child received message: Hello from Parent!
Parent received message: Hello from Child!
*/
