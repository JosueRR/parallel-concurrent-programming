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
    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
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
    int64_t cantidad_entradas = shared_data->listaDatos.usado;
    //int64_t entradas_por_trabajador;
    int64_t entradas_por_trabajador = cantidad_entradas / shared_data->thread_count;
   // printf("Size cantidad_entradas" "%" PRIu64 "\n", cantidad_entradas);
   // printf("Size trabajadores" "%" PRIu64 "\n", shared_data->thread_count);
   // Si hay más hilos que entradas por default solo procesan una por hilo
    if (shared_data->thread_count > cantidad_entradas) {
        entradas_por_trabajador = 1;
         //printf("entro 1\n");
    } else {
        // Se distribuyen las entradas entre los hilos
        //printf("entro 2\n");
        //entradas_por_trabajador = ceil(cantidad_entradas / shared_data->thread_count);
        //printf("Entradas por trabajador " "%" PRIu64 "\n", entradas_por_trabajador);
    }

    int64_t ultimo_indice = 0;
    bool continuar = true;
    for (int64_t i = 0; i < shared_data->thread_count; ++i) {
         //printf("OJO ULTIMO INDICE ----->" "%" PRIu64 "\n", ultimo_indice);
       //  printf("entro 3\n");
        if (continuar) {
        private_data[i].tieneTrabajo = true;
        private_data[i].indiceBase = ultimo_indice;
        ultimo_indice += entradas_por_trabajador;
        // Verifica si ya no hay indices para el siguiente trabajadaro
        if (ultimo_indice >= cantidad_entradas) {
            ultimo_indice = cantidad_entradas;
            continuar = false;
        }
        // Verifica si ya no quedan más trabajadores, y toma el resto de trabajos
        if (i == shared_data->thread_count - 1) {
            ultimo_indice = cantidad_entradas;
        }
         private_data[i].indiceFinal = ultimo_indice - 1;
        } else {
         private_data[i].tieneTrabajo = false;
        }
    }

    // for (int contadorHilos = 0; contadorHilos < shared_data->thread_count; contadorHilos++) {
    //     printf("El hilo %i\n",contadorHilos);
    //     if (private_data[contadorHilos].tieneTrabajo)
    //     {
    //         printf("Tiene trabajo\n");
    //     } else {
    //         printf("No tiene trabajo\n");
    //     }
    //     printf("El indice inicial es: " "%" PRIu64 "\n", private_data[contadorHilos].indiceBase);
    //     printf("El indice final es: " "%" PRIu64 "\n", private_data[contadorHilos].indiceFinal);
    //     printf("-------------------------\n");
    // }


//     int64_t cantidad_entradas = shared_data->listaDatos.usado;
//     int64_t entradas_por_trabajador;
//    // printf("Size cantidad_entradas" "%" PRIu64 "\n", cantidad_entradas);
//    // printf("Size trabajadores" "%" PRIu64 "\n", shared_data->thread_count);
//     if (shared_data->thread_count > cantidad_entradas) {
//         entradas_por_trabajador = 1;
//          //printf("entro 1\n");
//     } else {
//         //printf("entro 2\n");
//         entradas_por_trabajador = cantidad_entradas / shared_data->thread_count;
//     }

//     int64_t ultimo_indice = 0;
//     bool continuar = true;
//     for (int64_t i = 0; i < shared_data->thread_count; ++i) {
//          //printf("OJO ULTIMO INDICE ----->" "%" PRIu64 "\n", ultimo_indice);
//        //  printf("entro 3\n");
//         if (continuar) {
//         private_data[i].tieneTrabajo = true;
//         private_data[i].indiceBase = ultimo_indice;
//         ultimo_indice += entradas_por_trabajador;
//         // Verifica si ya no hay indices para el siguiente trabajadaro
//         if (ultimo_indice >= cantidad_entradas) {
//             ultimo_indice = cantidad_entradas;
//             continuar = false;
//         }
//         // Verifica si ya no quedan más trabajadores, y toma el resto de trabajos
//         if (i == shared_data->thread_count - 1) {
//             ultimo_indice = cantidad_entradas;
//         }
//          private_data[i].indiceFinal = ultimo_indice - 1;
//         } else {
//          private_data[i].tieneTrabajo = false;
//         }
//     }
    
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
        for (int64_t thread_number = 0; thread_number < shared_data->thread_count; ++thread_number) {
            private_data[thread_number].shared_data = shared_data;
            error = pthread_create(&threads[thread_number], /*attr*/ NULL, calcularParallel
            , /*arg*/ &private_data[thread_number]);
            if (error == EXIT_SUCCESS) {
            } else {
                fprintf(stderr, "Error: could not create secondary thread\n");
                break;
            }
        }
        // Limpia la memoria
        for (int64_t thread_number = 0; thread_number < shared_data->thread_count
        ; ++thread_number) {

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
        for (int64_t i = private_data->indiceBase; i <= private_data->indiceFinal ; ++i) {
            private_data->shared_data->listaDatos.arreglo[i] = calcularFactores(private_data->shared_data->listaDatos.arreglo[i]);
        }
    }
    return NULL;
}
