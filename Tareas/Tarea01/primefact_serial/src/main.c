/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Main del proyecto
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "prime_fact.h"

int main(int argc, char *argv[]) {
    // Almacena la entrada del usuario
    FILE* entrada = stdin;
    // Almacenan la entrada del usuario
    char linea[25];
    int64_t datoLeido = 0;
    // Almacenan la lista de factores y su tamaño
    int64_t* arregloFactores = NULL;
    int64_t tamanioArreglo = 0;

    // Bucle que se repite mientras existan elementos
    while ((fscanf(entrada, "%s", linea) == 1)) {
        // En caso de un valor ser válido se obtienen los factores
        datoLeido = lecturaDatos(linea);
        if ((datoLeido > 1)
        && (datoLeido != INVALID_NUMBER)) {
            // Se calculan los factores y se imprimen
            tamanioArreglo = 30;
            arregloFactores = (int64_t*) calloc(tamanioArreglo, sizeof(int64_t));
            if (arregloFactores) {
                arregloFactores = calcularFactores(datoLeido, arregloFactores, &tamanioArreglo);
                impresionDatos(datoLeido, arregloFactores, &tamanioArreglo);
                free(arregloFactores);
            }
        // En caso de no ser válido se busca el tipo de error y se imprime
        } else if ((linea[0] == '0')) {
            printf("0: NA\n");
        } else if (datoLeido == NA_1) {
            printf("1: NA\n");
        } else if ((linea[0] == '-')) {
            printf("%" PRId64 ": ", datoLeido);
            printf("invalid number\n");
        } else {
            printf("invalid number\n");
        }
    }
    return 0;
}
