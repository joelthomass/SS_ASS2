#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *data;

    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    strcpy(data, "Hello, Shared Memory!");
    printf("Data written to shared memory: %s\n", data);

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat (read-only) failed");
        return 1;
    }

    printf("Attempting to overwrite data in read-only mode...\n");
    // This check prevents the segmentation fault
    if (data) {
        printf("Current data in shared memory: %s\n", data);
        printf("Overwriting in read-only mode is not allowed.\n");
    }

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        return 1;
    }

    printf("Shared memory removed successfully.\n");
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *data;

    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    strcpy(data, "Hello, Shared Memory!");
    printf("Data written to shared memory: %s\n", data);

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    data = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (data == (char *)(-1)) {
        perror("shmat (read-only) failed");
        return 1;
    }

    printf("Attempting to overwrite data in read-only mode...\n");
    // This check prevents the segmentation fault
    if (data) {
        printf("Current data in shared memory: %s\n", data);
        printf("Overwriting in read-only mode is not allowed.\n");
    }

    if (shmdt(data) == -1) {
        perror("shmdt failed");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        return 1;
    }

    printf("Shared memory removed successfully.\n");
    return 0;
}
*/
