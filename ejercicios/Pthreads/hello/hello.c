// Copyright 2021 Josue Retana

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void* greet(void* data);


int main() {
    // Create_thread(greet)
    pthread_t thread;
    int error = pthread_create(&thread, NULL, greet, NULL);
    if (error == EXIT_SUCCESS) {
        // Print("Hello from main thread")
        printf("Hello from main thread\n");
        pthread_join(thread, NULL);
    } else {
        fprintf(stderr, "Error: could no create secondary thread\n");
    }
    return error;
}

// Procedure greet
void* greet(void* data) {
    printf("Hello from secondary thread\n");
    return NULL;
}
