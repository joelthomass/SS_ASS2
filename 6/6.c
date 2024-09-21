#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Thread %ld is running\n", (long)arg);
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
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/6$ gcc -o 6 6.c
joelthomas@joelthomas-82EY:~/Desktop/IIITB/SS/handsonlist2solutions/6$ ./6
Thread 1 is running
Thread 2 is running
Thread 3 is running
*/
