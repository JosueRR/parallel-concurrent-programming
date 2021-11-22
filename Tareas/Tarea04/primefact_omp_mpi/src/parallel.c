/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include "parallel.h"

void calcParallel(int argc, char* argv[], EstructuraArreglo *listaEntrada) {
    // Set cantidad de hilos
    int thread_count = omp_get_max_threads();
    if (argc == 2) {
        if (sscanf(argv[1], "%i", &thread_count) == 1) {
        } else {
        fprintf(stderr, "Error: invalid thread count\n");
        }
    }
    // Calcula número primos de forma paralela
    for (int i = 0; i < listaEntrada->usado; i++) {
        calcularFactores(&listaEntrada->arreglo[i]);
    }
}
