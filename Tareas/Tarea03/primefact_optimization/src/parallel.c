/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include "parallel.h"
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void initParalelizador(int argc, char* argv[], EstructuraArreglo arreglo) {
    int error = EXIT_SUCCESS;
    // Set cantidad de hilos
    uint64_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2) {
        if (sscanf(argv[1], "%" SCNu64, &thread_count) == 1) {
        } else {
        fprintf(stderr, "Error: invalid thread count\n");
        }
    }
    // Set shared_data
    shared_data_t* shared_data = (shared_data_t*)
    calloc(1, sizeof(shared_data_t));
    if (shared_data) {
        shared_data->listaDatos = arreglo;
        shared_data->thread_count = thread_count;
        shared_data->next_unit = 0;
        shared_data->consumed_count = 0;
        shared_data->unit_count = arreglo.usado;
        error = pthread_mutex_init(&shared_data->can_access_next_unit,
            /*attr*/ NULL);
        error = pthread_mutex_init(&shared_data->can_access_consumed_count,
            /*attr*/ NULL);
        if (error == EXIT_SUCCESS) {
            if (shared_data->listaDatos.arreglo) {
                createThreads(shared_data);
            }
            pthread_mutex_destroy(&shared_data->can_access_next_unit);
            pthread_mutex_destroy(&shared_data->can_access_consumed_count);
            free(shared_data);
        } else {
            fprintf(stderr, "Error: could not init mutex\n");
        }
    } else {
        fprintf(stderr, "Error: could not allocate shared data\n");
    }
}

void repartirTareas(shared_data_t* shared_data, private_data_t* private_data) {
    int64_t index_a_trabajar = 0;
    pthread_mutex_lock(&shared_data->can_access_next_unit);
    index_a_trabajar = shared_data->next_unit;
    shared_data->next_unit += 1;
    private_data->my_unit = index_a_trabajar;
    pthread_mutex_unlock(&shared_data->can_access_next_unit);
}

void createThreads(shared_data_t* shared_data) {
    // Almacena valor de un posible error
    int error = EXIT_SUCCESS;

    // Arreglo de pthreads y memoria privada
    pthread_t* threads = (pthread_t*)
        malloc(shared_data->thread_count * sizeof(pthread_t));
    private_data_t* private_data = (private_data_t*)
        calloc(shared_data->thread_count, sizeof(private_data_t));
    // Le asigna a cada hilo un índice de donde empezar y de donde finalizar
    if (threads && private_data) {
        //repartirTareas(shared_data);

        // Crea los hilos
        for (int64_t thread_number = 0;
         thread_number < shared_data->thread_count; ++thread_number) {
            private_data[thread_number].shared_data = shared_data;
            /*OJO BORRAR*/ private_data[thread_number].thread_number = thread_number;
            error = pthread_create(&threads[thread_number],
            /*attr*/ NULL, calcularParallel
            , /*arg*/ &private_data[thread_number]);
            if (error == EXIT_SUCCESS) {
            } else {
                fprintf(stderr, "Error: could not create secondary thread\n");
                break;
            }
        }
        // Limpia la memoria
        for (int64_t thread_number = 0;
        thread_number < shared_data->thread_count; ++thread_number) {
            pthread_join(threads[thread_number], /*value_ptr*/ NULL);
        }
        free(private_data);
        free(threads);
    } else {
    fprintf(stderr, "Error: could not allocate %" PRIu64 " threads\n"
      , shared_data->thread_count);
    }
}

// procedure calcularParallel
void* calcularParallel(void* data) {
    assert(data);
    private_data_t* private_data = (private_data_t*) data;
    shared_data_t* shared_data = private_data->shared_data;

    // Mientras existan elementos por calcular
    while (true) {
        pthread_mutex_lock(&shared_data->can_access_consumed_count);
        if (shared_data->consumed_count < shared_data->unit_count) {
            shared_data->consumed_count = shared_data->consumed_count + 1;
        } else {
            pthread_mutex_unlock(&shared_data->can_access_consumed_count);
            break;
        }
        pthread_mutex_unlock(&shared_data->can_access_consumed_count);
        repartirTareas(shared_data, private_data);
        private_data->shared_data->listaDatos.arreglo[private_data->my_unit]=
        calcularFactores(private_data->shared_data->listaDatos.arreglo[private_data->my_unit]);
    }

    return NULL;
}
