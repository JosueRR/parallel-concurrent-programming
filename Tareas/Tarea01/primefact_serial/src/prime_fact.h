/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef PRIME_FACT_H
#define PRIME_FACT_H
#include <stdint.h>
#include <stdio.h>

/*Códigos para posibles errores*/
// En caso de que sea un dato inválido
#define INVALID_NUMBER 0
// En caso de que el número sea 1
#define NA_1 1

/* Subrutinas */

/**
 @brief Lee una línea de texto y clasifica el tipo de número según el caso
 @param linea char* numero recibe una línea en forma de puntero
 @return un dato tipo int64_t:
   Si es un número válido retorna el numero == dato.
   0 == INVALID_NUMBER, si el valor se encuentra fuera del rango del int64_t
   1 == NA_1, en caso de que el número sea 1
   numero = 0, si el char es 0
   numero = strtoull(linea, NULL, 10), en caso de que el número sea negativo o inválido
*/
int64_t lecturaDatos(char* linea);

/**
 @brief Calcula los factores primos y los agrega a un arreglo
 @param numero el numero al cual se le calculan los factores primos
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArreglo contiene el tamaño del arreglo
 @return un arreglo tipo int64_t que contiene los factores del número
*/
int64_t* calcularFactores(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);

/**
 @brief Agrega elementos a un arreglo
 @param numero el numero que se debe agregar al arreglo
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArreglo contiene el tamaño del arreglo
 @return un arreglo tipo int64_t
*/
int64_t* agregarElemento(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);

/**
 @brief Imprime en consola el numero y sus factores primos
 @param numero el numero base que se imprime
 @param arregloFactores un arreglo que contiene los factores del número
 @param tamanioArreglo contiene el tamaño del arreglo
 @return no retorna valores, sin embargo el finalizar en salida estándar se tendrá el número seguido de la lista de factores primos
*/
void impresionDatos(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);

#endif  // PRIME_FACT_H
