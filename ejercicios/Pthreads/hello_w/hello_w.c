// Copyright 2021 Josué Retana - UCR

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // para dormir al hilo, para saber cantidad de hilos

/**
 * @brief ...
 */
void* greet(void* data);

// procedure main:
int main(int argc, char* argv[]) {
    int error = EXIT_SUCCESS;
    // for (int index = 0; index < argc; index++)
    // {
        // printf("argv[%d] = '%s'\n", index, argv[index]);
    // }
    // return 0;
    uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN); // strtol(argv[1]);
    if (argc == 2) {
        if (sscanf(argv[1], "%ld", &thread_count) ==  1) {
        } else {
                fprintf(stderr, "Error: invalid number of threads\n");
                return EXIT_FAILURE;
        }
    }
    pthread_t* threads = (pthread_t*) malloc(thread_count* sizeof(pthread_t));
    if (threads) {
        for (uint64_t thread_number = 0; thread_number < thread_count; ++thread_number) {
            error = pthread_create(&threads[thread_number], /*attr*/ NULL, greet, /*arg*/ (void*) thread_number); // alloc
            if (error == EXIT_SUCCESS) {
            } else {
                fprintf(stderr, "Error: could not create secondary thread\n");
            }
        }

        // Print main thread
        printf("Hello from main thread\n");

        // Libera los hilos, fuera del for para que sea concurrente. Libera memoria
        for (uint64_t thread_number = 0; thread_number < thread_count; ++thread_number) {
            pthread_join(threads[thread_number], /*value_ptr*/ NULL); // como el destroy
        }
        free(threads);

    } else {
        fprintf(stderr, "Error: invalid thread count\n");
        error = EXIT_FAILURE;
    }
    return error;
}  // end procedure

// procedure greet: // puntero a función
void* greet(void* data) {
  const uint64_t rank = (uint64_t) data;
  // print "Hello from n thread"
  printf("Hello from thread %ld\n", rank);
  return NULL;
}  // end procedure
