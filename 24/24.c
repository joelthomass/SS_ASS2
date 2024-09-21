#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65); 
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT); 
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message queue key: %d\n", key);
    printf("Message queue ID: %d\n", msgid);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/24$ touch progfile
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/24$ gcc -o 24 24.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/24$ ./24
Message queue key: 1090868082
Message queue ID: 0
*/
