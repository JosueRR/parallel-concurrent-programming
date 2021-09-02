// Contiene y define lo que compone la clase

#ifndef PRIME_FACT_H
#define PRIME_FACT_H

#include <stdint.h>
#include <stdio.h>

#define ERR_NUM_INVALIDO 1

/* Métodos */

// Lee una línea de texto
uint64_t lecturaDatos(char* linea);

// Calcula los factores primos y los agrega a una lista
uint64_t calculoFactores(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo);

// Imprime una lista con los factores primos de un número dado
void impresionDatos(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo);

#endif // PRIME_FACT_H