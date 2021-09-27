/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Main del proyecto
*/

#include <stdlib.h>
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
    return 0;
}
