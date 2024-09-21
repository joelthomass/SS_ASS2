#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65); // Generate unique key
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    msgid = msgget(key, 0666 | IPC_CREAT); // Create a message queue
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    printf("Message queue created with ID: %d\n", msgid);
    return 0;
}

