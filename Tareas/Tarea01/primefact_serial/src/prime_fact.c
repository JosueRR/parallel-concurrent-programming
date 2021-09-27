/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "prime_fact.h"

/* LECTURA Y VALIDACIÓN */

EstructuraArreglo lecturaDatos(FILE* entrada, EstructuraArreglo arreglo) {
    // Representa las lineas de entrada
    char linea[BUFFER_MAX];
    // Struct con la información relacionada a un número
    BloqueDatos ingresoUsuario;
    // Sirve como indice
    int contador = 0;
    // Itera sobre la entrada, se asigna y valida información
    while (fscanf(entrada, "%s", linea) == 1) {
        insertArray(&arreglo, ingresoUsuario);
        arreglo.arreglo[contador] = validarEntrada(linea, arreglo, contador);
        contador++;
    }
    return arreglo;
}

BloqueDatos validarEntrada(char* linea, EstructuraArreglo arreglo,
int contador) {
    // Asigna el posible número
    int64_t numero;
    // Asigna el ingreso como válido a priori
    arreglo.arreglo[contador].valido = false;
    // Asigna tamaño básico al arreglo de factores
    arreglo.arreglo[contador].tamanioArregloFactores = BLOCK_SIZE;
    // Asigna el char
    strncpy(arreglo.arreglo[contador].charIngreso, linea, strlen(linea) + 1);

    // Se lee el posible número y se realizan las verificaciones a priori
    if (strlen(linea) && linea[0] != '-'
    && linea[0] != '0' && linea[0] != '1'
    && linea[1] != '\0'
    && isdigit(linea[0])) {
        numero = strtoull(linea, NULL, 10);
        arreglo.arreglo[contador].numero = numero;
        arreglo.arreglo[contador].valido = true;
        return arreglo.arreglo[contador];
    }

    // En caso de que el número supera el espacio de int64_t
    if (strtoull(linea, NULL, 10) == ULLONG_MAX
    && strstr(linea, "18446744073709551615") == NULL
    && strlen(linea) >= strlen("18446744073709551615")) {
        numero = INVALID_NUMBER;
        arreglo.arreglo[contador].numero = numero;
        arreglo.arreglo[contador].valido = false;
        return arreglo.arreglo[contador];
    }

    // En caso de ser negativo se considera como INVALID_NUMBER
    if ((linea[0] == '-') && isdigit(linea[1])) {
        numero = INVALID_NUMBER;
        arreglo.arreglo[contador].numero = numero;
        arreglo.arreglo[contador].valido = false;
        return arreglo.arreglo[contador];
    }

    // En caso de ser 1 se considera como NA_1
    if (linea[0] == '1' && linea[1] == '\0') {
        numero = NA_1;
        arreglo.arreglo[contador].numero = numero;
        arreglo.arreglo[contador].valido = false;
        return arreglo.arreglo[contador];
    }

    // En caso de ser 0 se considera como numero, pero inválido
    if (linea[0] == '0' && linea[1] == '\0') {
        numero = 0;
        arreglo.arreglo[contador].numero = numero;
        arreglo.arreglo[contador].valido = false;
        return arreglo.arreglo[contador];
    }

    // Cast para conseguir el número
    numero = strtoull(linea, NULL, 10);

    // Se verifica que sea un número y no un caracter
    if (isdigit(linea[0])) {
        arreglo.arreglo[contador].valido = true;
    }
    arreglo.arreglo[contador].numero = numero;
    return arreglo.arreglo[contador];
}

void initArray(EstructuraArreglo *a, int initialSize) {
  a->arreglo = malloc(initialSize * sizeof(BloqueDatos));
  a->usado = 0;
  a->tamanio = initialSize;
}

void insertArray(EstructuraArreglo *a, BloqueDatos element) {
  if (a->usado == a->tamanio) {
    a->tamanio *= 2;
    a->arreglo = realloc(a->arreglo, a->tamanio * sizeof(BloqueDatos));
  }
  a->arreglo[a->usado++] = element;
}

void freeArray(EstructuraArreglo *a) {
  free(a->arreglo);
  a->arreglo = NULL;
  a->usado = a->tamanio = 0;
}

/* CALCULO DE FACTORES */

int64_t* calcularFactores(int64_t numero, int64_t* arregloFactores,
int64_t* tamanioArreglo) {
    // Adaptado de URL: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
    // Caso: número == par, entonces 2 es factor
    while (!(numero % 2)) {
        arregloFactores = agregarFactor(2, arregloFactores, tamanioArreglo);
        numero = numero / 2;
    }

    // Caso: número debe ser impar
    for (int64_t i = 3; i <= (int64_t) ceil(sqrt(numero)); i += 2) {
        while (!(numero % i)) {
            arregloFactores = agregarFactor(i, arregloFactores,
            tamanioArreglo);
            numero = numero / i;
        }
    }

    // Caso: número es un primo mayor a 2
    if (numero > 2) {
        arregloFactores = agregarFactor(numero, arregloFactores,
        tamanioArreglo);
    }

  return arregloFactores;
}

BloqueDatos asignarListaFactores(EstructuraArreglo arreglo, int indice) {
    // Inicializa y asigna un arreglo de factores
    arreglo.arreglo[indice].arregloFactores = (int64_t*)
    calloc(arreglo.arreglo[indice].tamanioArregloFactores, sizeof(int64_t));
    if (arreglo.arreglo[indice].arregloFactores) {
        arreglo.arreglo[indice].arregloFactores = calcularFactores(
        arreglo.arreglo[indice].numero, arreglo.arreglo[indice].arregloFactores,
        &arreglo.arreglo[indice].tamanioArregloFactores);
        return arreglo.arreglo[indice];
    }
    return arreglo.arreglo[indice];
}

int64_t* agregarFactor(int64_t numero, int64_t*
arregloFactores, int64_t* tamanioArreglo) {
    // Si arreglo == lleno, se crea uno nuevo (incluyendo los nuevos datos)
    if (arregloFactores[*tamanioArreglo - 1]) {
        // Se copian los datos en el arreglo nuevo
        int64_t* arregloCopia = (int64_t*)
        calloc(*tamanioArreglo + 20, sizeof(int64_t));
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
            arregloFactores[i] = numero;
            agregado = 1;
        }
    }
    return arregloFactores;
}

/* IMPRESIÓN */

void printArregloFactores(int64_t numero,
int64_t* arregloFactores, int64_t* tamanioArreglo) {
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

void printResult(EstructuraArreglo arreglo) {
    for (int indice = 0; indice < arreglo.usado; indice++) {
        // Si el numero es válido lo imprime junto con sus factores
        if (arreglo.arreglo[indice].valido) {
            printArregloFactores(arreglo.arreglo[indice].numero,
            arreglo.arreglo[indice].arregloFactores,
            &arreglo.arreglo[indice].tamanioArregloFactores);
        // En caso de no ser válido se busca el tipo de error y se imprime
        } else {
            if ((arreglo.arreglo[indice].charIngreso[0] == '0')
            && (arreglo.arreglo[indice].charIngreso[1] == '\0')) {
             printf("0: NA\n");
            } else if (arreglo.arreglo[indice].numero == NA_1
            && (arreglo.arreglo[indice].charIngreso[1]== '\0')) {
                printf("1: NA\n");
            } else if ((arreglo.arreglo[indice].charIngreso[0] == '-')
            && isdigit(arreglo.arreglo[indice].charIngreso[1])) {
                printf("%s", arreglo.arreglo[indice].charIngreso);
                printf(": invalid number\n");
            } else {
                printf("invalid number\n");
            }
        }
    }
}
