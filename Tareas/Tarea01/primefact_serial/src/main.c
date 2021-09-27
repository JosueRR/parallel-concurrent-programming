/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Main del proyecto
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include "prime_fact.h"

int main() {
    // Almacena la entrada del usuario
    FILE* entrada = stdin;
    // Almacena las entradas del usuario
    EstructuraArreglo arreglo;

    // Crea el arreglo
    initArray(&arreglo, BLOCK_SIZE);
    arreglo = lecturaDatos(entrada, arreglo);

    // Calcula factores
    for (int i = 0; i < arreglo.usado; i++) {
       if (arreglo.arreglo[i].valido == true) {
           arreglo.arreglo[i] = asignarListaFactores(arreglo, i);
       }
    }

    // Imprime el resultado
    printResult(arreglo);

    // Libera memoria
    for (int i = 0; i < arreglo.usado; i++) {
        if (arreglo.arreglo[i].valido == true) {
            free(arreglo.arreglo[i].arregloFactores);
        }
    }
    freeArray(&arreglo);

    // // Bucle que se repite mientras existan elementos
    // while (fscanf(entrada, "%s", linea) == 1) {
    //     // En caso de un valor ser válido se obtienen los factores
    //     datoLeido = lecturaDatos(linea);
    //     if ((datoLeido > 1)
    //     && (datoLeido != INVALID_NUMBER)) {
    //         // Se calculan los factores y se imprimen
    //         tamanioArreglo = 30;
    //         arregloFactores = (int64_t*)
    //         calloc(tamanioArreglo, sizeof(int64_t));
    //         if (arregloFactores) {
    //             arregloFactores = calcularFactores(datoLeido,
    //             arregloFactores, &tamanioArreglo);
    //             impresionDatos(datoLeido, arregloFactores, &tamanioArreglo);
    //             free(arregloFactores);
    //         }
    //     // En caso de no ser válido se busca el tipo de error y se imprime
    //     } else if ((linea[0] == '0') && (linea[1] == '\0')) {
    //         printf("0: NA\n");
    //     } else if (datoLeido == NA_1 && (linea[1] == '\0')) {
    //         printf("1: NA\n");
    //     } else if ((linea[0] == '-') && isdigit(linea[1])) {
    //         printf("%s", linea);
    //         printf(": invalid number\n");
    //     } else {
    //         printf("invalid number\n");
    //     }
    // }
    return 0;
}
