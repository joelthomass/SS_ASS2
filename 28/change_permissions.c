#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_info;

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

    // Get the current permissions and other information
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl IPC_STAT failed");
        return 1;
    }

    // Display current permissions
    printf("Current permissions: %o\n", msg_info.msg_perm.mode);

    // Change the permissions (e.g., to read/write for owner, group, others)
    msg_info.msg_perm.mode = 0644; // New permissions
    if (msgctl(msgid, IPC_SET, &msg_info) == -1) {
        perror("msgctl IPC_SET failed");
        return 1;
    }

    // Confirm the change
    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl IPC_STAT failed");
        return 1;
    }

    // Display new permissions
    printf("New permissions: %o\n", msg_info.msg_perm.mode);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/28$ gcc -o createq createq.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/28$ ./createq
Message queue created with ID: 4
*/
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/28$ ./change_permissions
Current permissions: 666
New permissions: 644
*/
