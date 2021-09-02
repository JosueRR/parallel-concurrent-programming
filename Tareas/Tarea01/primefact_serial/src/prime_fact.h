// Contiene y define lo que compone la clase

#ifndef PRIME_FACT_H
#define PRIME_FACT_H
#include <stdint.h>
#include <stdio.h>

#define INVALID_NUMBER 0
#define NA 1

/* Métodos */

// Lee una línea de texto
uint64_t lecturaDatos(char* linea);

// Agrega elementos a un arreglo
uint64_t* agregarElemento(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo);

// Calcula los factores primos y los agrega a un arreglo
uint64_t* calcularFactores(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo);

// Imprime una arreglo con los factores primos de un número dado
void impresionDatos(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo);


#endif // PRIME_FACT_H