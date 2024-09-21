#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;

    // Generate a unique key
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }

    // Access the message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        return 1;
    }

    printf("Message queue removed successfully.\n");
    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/29$ gcc -o createq createq.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/29$ ./createq
Message queue created with ID: 5
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/29$ ./remove_queue
Message queue removed successfully.
*/
