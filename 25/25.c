#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_info;

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

    if (msgctl(msgid, IPC_STAT, &msg_info) == -1) {
        perror("msgctl failed");
        return 1;
    }

    printf("Access Permissions: %o\n", msg_info.msg_perm.mode);
    printf("User ID (UID): %d\n", msg_info.msg_perm.uid);
    printf("Group ID (GID): %d\n", msg_info.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&msg_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&msg_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&msg_info.msg_ctime));
    printf("Size of the Queue: %ld bytes\n", msg_info.__msg_cbytes);
    printf("Number of Messages in the Queue: %lu\n", msg_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", msg_info.msg_qbytes);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/25$ gcc -o createq createq.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/25$ ./createq
Message queue created with ID: 1
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/25$ ./25
Access Permissions: 666
User ID (UID): 1000
Group ID (GID): 1000
Time of Last Message Sent: Thu Jan  1 05:30:00 1970
Time of Last Message Received: Thu Jan  1 05:30:00 1970
Time of Last Change: Sat Sep 21 15:17:44 2024
Size of the Queue: 0 bytes
Number of Messages in the Queue: 0
Maximum Number of Bytes Allowed: 16384
*/
