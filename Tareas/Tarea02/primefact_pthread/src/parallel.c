/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include "parallel.h"
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void initParalelizador(int argc, char* argv[], EstructuraArreglo arreglo) {
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

        if (shared_data->listaDatos.arreglo) {
            createThreads(shared_data);
        }
        free(shared_data);
    }
}

void repartirTareas(shared_data_t* shared_data, private_data_t* private_data) {
    // Almacena cantidad de entradas
    int64_t cantidadNumeros = shared_data->listaDatos.usado;
    // Almacena cantidad de entradas que se deben procesar por hilo
    int64_t numerosPorHilo = cantidadNumeros / shared_data->thread_count;
    // Almacena el valor del índice final a asignar
    int64_t indiceFinal = 0;

    // Si hilos > numeros, por default solo se procesa un número por hilo
    if (shared_data->thread_count > cantidadNumeros) {
        numerosPorHilo = 1;
    }

    bool continuar = true;
    for (int64_t thread_number = 0; thread_number < shared_data->thread_count;
    ++thread_number) {
        if (continuar) {
        // Verifica que aún hayan tareas pr hacer
        if (indiceFinal >= cantidadNumeros) {
            indiceFinal = cantidadNumeros;
            continuar = false;
        }

        // Asigna el hilo con tarea
        private_data[thread_number].tieneTrabajo = true;
        private_data[thread_number].indiceBase = indiceFinal;
        indiceFinal += numerosPorHilo;

        // Si ya no hay más hilos, se le asigna el resto de tareas al último
        if (thread_number == shared_data->thread_count - 1) {
            indiceFinal = cantidadNumeros;
        }
         private_data[thread_number].indiceFinal = indiceFinal - 1;
        } else {
         private_data[thread_number].tieneTrabajo = false;
        }
    }
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
        repartirTareas(shared_data, private_data);

        // Crea los hilos
        for (int64_t thread_number = 0;
         thread_number < shared_data->thread_count; ++thread_number) {
            private_data[thread_number].shared_data = shared_data;
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
    if (private_data->tieneTrabajo) {
        for (int64_t i = private_data->indiceBase;
        i <= private_data->indiceFinal ; ++i) {
            private_data->shared_data->listaDatos.arreglo[i]=
            calcularFactores(private_data->shared_data->listaDatos.arreglo[i]);
        }
    }
    return NULL;
}
