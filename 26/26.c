#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

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

    message.msg_type = 1; // Message type
    strcpy(message.msg_text, "Hello, this is a test message!");

    // Send the message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Message sent: %s\n", message.msg_text);
    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/26$ touch progfile
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/26$ gcc -o createq createq.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/26$ ./createq
Message queue created with ID: 2
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/26$ ./26
Message sent: Hello, this is a test message!
*/
