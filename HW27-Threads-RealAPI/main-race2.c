#include <stdio.h>

#include "mythreads.h"

int balance = 0;
pthread_mutex_t m;

void* worker(void* arg) {
    Pthread_mutex_lock(&m);
    balance++;
    Pthread_mutex_unlock(&m);
    // balance++; // unprotected access
    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t p;

    Pthread_mutex_init(&m, NULL);

    Pthread_create(&p, NULL, worker, NULL);
    Pthread_mutex_lock(&m);
    balance++; // unprotected access
    Pthread_mutex_unlock(&m);
    Pthread_join(p, NULL);
    return 0;
}
