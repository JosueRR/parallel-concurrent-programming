/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef PRIME_FACT_H
#define PRIME_FACT_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*Definicón Códigos*/
// Error: En caso de que sea un dato inválido
#define INVALID_NUMBER 0
// Error: En caso de que el número sea 1
#define NA_1 1
// Tamaño default para los char
#define BUFFER_MAX 56
// Tamaño default para bloques de memoria (memoria dinámica)
#define BLOCK_SIZE 5

/* Structs */

/**
 @brief Almacena todos los datos relacionados a una entrada por parte del usuario
 @param charIngreso almacena el char que ingreso el usuario
 @param validos indica si es o no, un número válido para calcular los factores
 @param numero almacena el número a calculos los factores
 @param arregloFactores almacena un arreglo con los factores del número
 @param tamanioArregloFactores almacena el tamaño de arregloFactores
*/
typedef struct BloqueDatos {
    char charIngreso[BUFFER_MAX];
    bool valido;
    int64_t numero;
    int64_t* arregloFactores;
    int64_t tamanioArregloFactores;
} BloqueDatos;

/**
 @brief Estructura de un arreglo
 @param arreglo arreglo de tipo BloqueDatos
 @param usado representa el tamaño usado del arreglo
 @param tamanio capacidad del arreglo, no representa el usado
*/
typedef struct EstructuraArreglo {
  BloqueDatos *arreglo;
  int usado;
  int tamanio;
} EstructuraArreglo;

/* SUBRUTINAS */

/* LECTURA Y VALIDACIÓN */

/**
 @brief Lee las líneas ingresadas por el usuario y crea un arreglo dinámico
 @param entrada representa la entrada del usuario
 @param arreglo arreglo de Bloques de datos relacionados a la entrada
 @return arreglo con los datos ingresados por el usuario.
  indirectamente llama al método que valida la entrada.
*/
EstructuraArreglo lecturaDatos(FILE* entrada, EstructuraArreglo arreglo);

/**
 @brief Valida una línea especificada de la entrada del usuario 
 @param linea representa la linea ingresada por el usuario
 @param arreglo arreglo de Bloques de datos relacionados a la entrada
 @param contador representa el índice de la entrada a validar
 @return un bloque de datos, este bloque: se realizó una copia de la entrada, 
    se determinó si es válida la entrada, se realizó el cast a número.
*/
BloqueDatos validarEntrada(char* linea,
EstructuraArreglo arreglo, int contador);

/**
 @brief Inicializa un arreglo de bloque de datos
 @param arreglo arreglo de datos
 @param defaultTamanio tamaño por defecto del arreglo
*/
void initArray(EstructuraArreglo *arreglo, int defaultTamanio);

/**
 @brief Incerta un elemento en el arreglo de bloque de datos
 @param arreglo arreglo de datos
 @param element elemento a ingresar al arreglo
*/
void insertArray(EstructuraArreglo *arreglo, BloqueDatos element);

/**
 @brief Libera la memoria utiliza por el arreglo
 @param arreglo arreglo de datos
*/
void freeArray(EstructuraArreglo *arreglo);

/* CALCULO DE FACTORES */

/**
 @brief Algoritmo que calcula los factores primos y los agrega a un arreglo de factores
 @param numero el numero al cual se le calculan los factores primos
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArreglo contiene el tamaño del arreglo
 @return un arreglo tipo int64_t que contiene los factores del número
*/
int64_t* calcularFactores(int64_t numero, int64_t*
arregloFactores, int64_t* tamanioArreglo);

/**
 @brief Asigna una lista de factores a relacionada a un número
 @param arreglo arreglo de datos
 @param indice indica el índice donde se ubica el número
 @return un bloque de datos con una lista de factores asignada
*/
BloqueDatos asignarListaFactores(EstructuraArreglo arreglo, int indice);

/**
 @brief Agrega un factor a un arreglo de factores
 @param numero el numero que se debe agregar al arreglo
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArreglo contiene el tamaño del arreglo
 @return un arreglo tipo int64_t
*/
int64_t* agregarFactor(int64_t numero, int64_t*
arregloFactores, int64_t* tamanioArreglo);

/* IMPRESIÓN */

/**
 @brief Imprime en consola el numero y sus factores primos
 @param numero el numero base que se imprime
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArregloFactores contiene el tamaño del arreglo
 @return no retorna valores, sin embargo el finalizar en salida estándar se tendrá el número seguido de la lista de factores primos
*/
void printArregloFactores(int64_t numero, int64_t*
arregloFactores, int64_t* tamanioArregloFactores);

/**
 @brief Imprime en consola el resultado de la entrada del usuario
 @param arreglo arreglo de bloque de datos
*/
void printResult(EstructuraArreglo arreglo);

#endif  // PRIME_FACT_H
