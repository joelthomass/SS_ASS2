#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Receive message with flag 0
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed with flag 0");
        return 1;
    }
    printf("Received with flag 0: %s\n", message.msg_text);

    // Try to receive message with IPC_NOWAIT flag
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available (IPC_NOWAIT)\n");
        } else {
            perror("msgrcv failed with IPC_NOWAIT");
            return 1;
        }
    } else {
        printf("Received with IPC_NOWAIT: %s\n", message.msg_text);
    }

    return 0;
}
