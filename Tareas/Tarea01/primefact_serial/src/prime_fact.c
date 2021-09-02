// Implementación de las subrutinas

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include "prime_fact.h"

uint64_t lecturaDatos(char* linea)
{
    // Variable que almacena el posible número
    uint64_t numero = 0;

    // Se lee el posible número y se realizan las verificaciones a priori
    if (strlen(linea) && linea[0] != '-')
    {
        // Se convierte el valor leido a uint64_t
        numero = strtoull(linea, NULL, 10);
        return numero;
    }
    // En caso de ser 0 o 1 se considera como NA
    else if (strtoull(linea, NULL, 10) == 0 || strtoull(linea, NULL, 10) == 1)
    {
        return numero = NA;
    }
    // Cualquier otro caso será considerado invalid number
    return numero = INVALID_NUMBER;
}

// Calcula los factores primos y los agrega a un arreglo
// Adaptado de URL: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
uint64_t* calcularFactores(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo)
{
    // Caso: número == par, entonces 2 es factor
    while (!(numero % 2)) 
    {
        arregloFactores = agregarElemento(2, arregloFactores, tamanioArreglo);
        numero = numero / 2;
    }

    // Caso: número debe ser impar
    for (uint64_t i = 3; i <= (uint64_t) ceil(sqrt(numero)); i += 2) 
    {
        while (!(numero % i)) 
        {
            arregloFactores = agregarElemento(i, arregloFactores, tamanioArreglo);
            numero = numero / i;
        }
    }

    // Caso: número es un primo mayor a 2
    if (numero > 2) 
    {
        arregloFactores = agregarElemento(numero, arregloFactores, tamanioArreglo);
    }

  return arregloFactores;
}

uint64_t* agregarElemento(uint64_t n, uint64_t* arregloFactores, uint64_t* tamanioArreglo)
{
    // Se agrega el elemento al arreglo
    // Caso en que el arreglo ya está lleno, por lo tanto se crea uno nuevo (incluyendo los nuevos datos)
    if (arregloFactores[*tamanioArreglo - 1])
    {
        // Se copian los datos en el arreglo nuevo
        uint64_t* nueva_lista = (uint64_t*) calloc(*tamanioArreglo + 20, sizeof(uint64_t));
        for (uint64_t i = 0; i < *tamanioArreglo; ++i) 
        {
            nueva_lista[i] = arregloFactores[i];
        }
        // Se libera memoria y se copian los datos nuevos
        free(arregloFactores);
        *tamanioArreglo += 20;
        arregloFactores = nueva_lista;
    }
    // Se agrega el dato al arreglo
    char agregado = 0;
    for (uint64_t i = 0; i < *tamanioArreglo && !agregado; ++i) 
    {
        if (!arregloFactores[i]) 
        {
            arregloFactores[i] = n;
            agregado = 1;
        }
    }
    return arregloFactores;
}

void impresionDatos(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo)
{
    // Variables para imprimir los datos
    uint64_t indice = 0;
    uint64_t factor = 0;
    uint64_t potencia = 0;
    // Imprime el número
    printf("%" PRIu64 ":", numero);

    // Se imprimen las potencias y factores del arreglo
    while (arregloFactores[indice] && indice < *tamanioArreglo) 
    {
        factor = arregloFactores[indice];
        potencia = 0;

        while (factor == arregloFactores[indice]) 
        {
            ++potencia;
            ++indice;
        }
        
        if (potencia != 1) 
        {
            printf(" %" PRIu64 "^%" PRIu64, factor, potencia);
        }
        // Cuando la potencia es 1 se ignora 
        else 
        {
            printf(" %" PRIu64, factor);
        }
    }
    printf("\n");
}