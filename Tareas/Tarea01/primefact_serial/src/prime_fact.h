// Contiene y define lo que compone la clase

#ifndef PRIME_FACT_H
#define PRIME_FACT_H
#include <stdint.h>
#include <stdio.h>

/*Códigos para posibles errores*/
// En caso de que sea un dato inválido
#define INVALID_NUMBER 0
// En caso de que el número sea 1
#define NA_1 1

/* Métodos */

// Lee una línea de texto
int64_t lecturaDatos(char* linea);

// Agrega elementos a un arreglo
int64_t* agregarElemento(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);

// Calcula los factores primos y los agrega a un arreglo
int64_t* calcularFactores(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);

// Imprime una arreglo con los factores primos de un número dado
void impresionDatos(int64_t numero, int64_t* arregloFactores, int64_t* tamanioArreglo);


#endif // PRIME_FACT_H