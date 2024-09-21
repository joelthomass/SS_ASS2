#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    sem_t *binary_semaphore;
    sem_t *counting_semaphore;

    binary_semaphore = sem_open("/binary_semaphore", O_CREAT, 0644, 1);
    if (binary_semaphore == SEM_FAILED) {
        perror("sem_open (binary) failed");
        return 1;
    }
    printf("Binary semaphore created and initialized to 1.\n");

    counting_semaphore = sem_open("/counting_semaphore", O_CREAT, 0644, 5);
    if (counting_semaphore == SEM_FAILED) {
        perror("sem_open (counting) failed");
        sem_close(binary_semaphore);
        sem_unlink("/binary_semaphore");
        return 1;
    }
    printf("Counting semaphore created and initialized to 5.\n");

    sem_close(binary_semaphore);
    sem_close(counting_semaphore);
    sem_unlink("/binary_semaphore");
    sem_unlink("/counting_semaphore");

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/31$ gcc -o 31 31.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/31$ ./31
Binary semaphore created and initialized to 1.
Counting semaphore created and initialized to 5.
*/
