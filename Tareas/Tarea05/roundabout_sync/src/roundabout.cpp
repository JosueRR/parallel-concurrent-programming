/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Proyecto rotonda sincronizada
*/

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>
#include <vector>

/**
 @brief Datos compartidos entre hilos
 @param drive_min_delay rango de delay, mínimo
 @param drive_max_delay rango de delay, máximo
 @param verbose modo detallado, imprime el camino seguido
 @param semaphore_array arreglo de semáforos
*/
typedef struct {
    int64_t drive_min_delay = 0;
    int64_t drive_max_delay = 0;
    bool verbose = false;
    std::vector<sem_t> semaphore_array;
} shared_data_t;

int main(int argc, char* argv[]) {
    // Analyze arguments
    shared_data_t shared_data;
    shared_data.drive_min_delay = 0;
    shared_data.drive_max_delay = 0;
    shared_data.verbose = false;
    if (argc >= 3) {
        shared_data.drive_min_delay = atoi(argv[1]);
        shared_data.drive_max_delay = atoi(argv[2]);
    }
    if (argc >= 4) {
        if (strcmp(argv[3], "-v") == 0) {
            shared_data.verbose = true;
        }
    }
    return 0;
}

