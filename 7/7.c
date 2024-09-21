#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Thread %ld created with ID: %lu\n", (long)arg, pthread_self());
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, thread_function, (void*)1);
    pthread_create(&thread2, NULL, thread_function, (void*)2);
    pthread_create(&thread3, NULL, thread_function, (void*)3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
/*
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/7$ gcc -o 7 7.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/7$ ./7
Thread 2 created with ID: 140663781844672
Thread 1 created with ID: 140663790237376
Thread 3 created with ID: 140663773451968
*/
