#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

sem_t *ticket_semaphore;
sem_t *memory_semaphore;
sem_t *resource_semaphore;

void create_ticket_numbers(int ticket_count) {
    sem_wait(ticket_semaphore);
    printf("Creating %d ticket numbers:\n", ticket_count);
    for (int i = 1; i <= ticket_count; i++) {
        printf("Ticket number: %d\n", i);
    }
    sem_post(ticket_semaphore);
}

void write_to_shared_memory(const char *data) {
    sem_wait(memory_semaphore);
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT);
    char *shared_data = (char *)shmat(shmid, NULL, 0);
    if (shared_data == (char *)(-1)) {
        perror("shmat failed");
        sem_post(memory_semaphore);
        return;
    }
    strcpy(shared_data, data);
    printf("Data written to shared memory: %s\n", shared_data);
    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);
    sem_post(memory_semaphore);
}

void use_resources(int resource_id) {
    sem_wait(resource_semaphore);
    printf("Using resource %d\n", resource_id);
    sleep(1);
    printf("Resource %d released\n", resource_id);
    sem_post(resource_semaphore);
}

int main() {
    ticket_semaphore = sem_open("/ticket_semaphore", O_CREAT, 0644, 1);
    memory_semaphore = sem_open("/memory_semaphore", O_CREAT, 0644, 1);
    resource_semaphore = sem_open("/resource_semaphore", O_CREAT, 0644, 2);

    if (ticket_semaphore == SEM_FAILED || memory_semaphore == SEM_FAILED || resource_semaphore == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }

    create_ticket_numbers(5);
    write_to_shared_memory("Hello, Shared Memory!");
    use_resources(1);
    use_resources(2);

    sem_close(ticket_semaphore);
    sem_close(memory_semaphore);
    sem_close(resource_semaphore);
    sem_unlink("/ticket_semaphore");
    sem_unlink("/memory_semaphore");
    sem_unlink("/resource_semaphore");

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/32$ gcc -o 32 32.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/32$ ./32
Creating 5 ticket numbers:
Ticket number: 1
Ticket number: 2
Ticket number: 3
Ticket number: 4
Ticket number: 5
Data written to shared memory: Hello, Shared Memory!
Using resource 1
Resource 1 released
Using resource 2
Resource 2 released
*/
