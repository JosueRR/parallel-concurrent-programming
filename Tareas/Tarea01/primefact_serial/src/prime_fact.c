/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "prime_fact.h"

int64_t lecturaDatos(char* linea) {
    // Variable que almacena el posible número
    int64_t numero;

    // Se lee el posible número y se realizan las verificaciones a priori
    if (strlen(linea) && linea[0] != '-') {
        numero = strtoull(linea, NULL, 10);
        return numero;
    }

    // En caso de que el número supera el espacio de int64_t
    if (strtoull(linea, NULL, 10) == ULLONG_MAX
    && strstr(linea, "18446744073709551615") == NULL
    && strlen(linea) >= strlen("18446744073709551615")) {
        return numero = INVALID_NUMBER;
    }

    // En caso de ser 1 se considera como NA_1
    if (linea[0] == 1) {
        return numero = NA_1;
    }

    // En caso de ser 0 se considera como numero, pero inválido
    if (linea[0] == 0) {
        return numero = 0;
    }

    // Todos los otros casos serán considerados invalid number
    numero = strtoull(linea, NULL, 10);
    return numero;
}

int64_t* calcularFactores(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo) {
    // Adaptado de URL: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
    // Caso: número == par, entonces 2 es factor
    while (!(numero % 2)) {
        arregloFactores = agregarElemento(2, arregloFactores, tamanioArreglo);
        numero = numero / 2;
    }

    // Caso: número debe ser impar
    for (int64_t i = 3; i <= (int64_t) ceil(sqrt(numero)); i += 2) {
        while (!(numero % i)) {
            arregloFactores = agregarElemento(i, arregloFactores, tamanioArreglo);
            numero = numero / i;
        }
    }

    // Caso: número es un primo mayor a 2
    if (numero > 2) {
        arregloFactores = agregarElemento(numero, arregloFactores, tamanioArreglo);
    }

  return arregloFactores;
}

int64_t* agregarElemento(int64_t n, int64_t* arregloFactores, int64_t* tamanioArreglo) {
    // Caso en que el arreglo ya está lleno, por lo tanto se crea uno nuevo (incluyendo los nuevos datos)
    if (arregloFactores[*tamanioArreglo - 1]) {
        // Se copian los datos en el arreglo nuevo
        int64_t* arregloCopia = (int64_t*) calloc(*tamanioArreglo + 20, sizeof(int64_t));
        for (int64_t i = 0; i < *tamanioArreglo; ++i) {
            arregloCopia[i] = arregloFactores[i];
        }
        // Se libera memoria y se copian los datos nuevos
        free(arregloFactores);
        *tamanioArreglo += 20;
        arregloFactores = arregloCopia;
    }
    // Se agrega el dato al arreglo
    char agregado = 0;
    for (int64_t i = 0; i < *tamanioArreglo && !agregado; ++i) {
        if (!arregloFactores[i]) {
            arregloFactores[i] = n;
            agregado = 1;
        }
    }
    return arregloFactores;
}

void impresionDatos(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo) {
    // Variables para imprimir los datos
    int64_t indice = 0;
    int64_t factor = 0;
    int64_t potencia = 0;

    // Imprime el número
    printf("%" PRIu64 ":", numero);

    // Se imprimen las potencias y factores del arreglo
    while (arregloFactores[indice] && indice < *tamanioArreglo) {
        factor = arregloFactores[indice];
        potencia = 0;

        while (factor == arregloFactores[indice]) {
            ++potencia;
            ++indice;
        }
        // Cuando la potencia es 1 se ignora
        if (potencia != 1) {
            printf(" %" PRIu64 "^%" PRIu64, factor, potencia);
        } else {
            printf(" %" PRIu64, factor);
        }
    }
    printf("\n");
}
