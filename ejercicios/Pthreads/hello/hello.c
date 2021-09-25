// Copyright 2021 Josué Retana - UCR

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // para dormir al hilo

/**
 * @brief ...
 */
void* greet(void* data);

// procedure main:
int main(void) {
  // create_thread(greet)
  pthread_t thread;
  int error = pthread_create(&thread, /*attr*/ NULL, greet, /*arg*/ NULL); // alloc
  if (error == EXIT_SUCCESS) {
    // print "Hello from main thread"
    // usleep(1);  // indeterminism
    printf("Hello from main thread\n");
    pthread_join(thread, /*value_ptr*/ NULL); // como el destroy
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }
  return error;
}  // end procedure

// procedure greet: // puntero a función
void* greet(void* data) {
  (void)data;
  // print "Hello from secondary thread"
  printf("Hello from secondary thread\n");
  return NULL;
}  // end procedure
