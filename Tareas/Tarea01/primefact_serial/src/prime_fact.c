// Implementación de las subrutinas

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <prime_fact.h>


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
    else 
    {
        return numero;
    }
}

// Calcula los factores primos y los agrega a una lista
// Adaptado de URL: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
uint64_t calculoFactores(uint64_t numero, uint64_t* arregloFactores, uint64_t* tamanioArreglo)
{
    // Caso: número == par, entonces 2 es factor
    while (!(numero % 2)) 
    {
        arregloFactores = agregaEnLista(2, arregloFactores, tamanioArreglo);
        numero = numero / 2;
    }

    // Caso: número debe ser impar
    for (uint64_t i = 3; i <= (uint64_t) ceil(sqrt(numero)); i += 2) 
    {
        while (!(numero % i)) 
        {
            arregloFactores = agregaEnLista(i, arregloFactores, tamanioArreglo);
            numero = numero / i;
        }
    }

    // Caso: número es un primo mayor a 2
    if (numero > 2) 
    {
        arregloFactores = agregaEnLista(numero, arregloFactores, tamanioArreglo);
    }

  return arregloFactores;
}