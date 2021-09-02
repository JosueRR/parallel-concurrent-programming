// Main del proyecto

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "prime_fact.h"

int main(int argc, char **argv[])
{
    // Almacena la entrada del usuario
    FILE* entrada = stdin;
    // Almacenan la entrada del usuario
    char linea[25];
    uint64_t datoLeido = 0;
    // Almacenan la lista de factores y su tamaño
    uint64_t* arregloFactores = NULL;
    uint64_t tamanioArreglo = 0;

    // Bucle que se repite mientras existan elementos
    while (fscanf(entrada, "%s", linea) == 1) 
    {
        // En caso de ser válido se obtienen los factores
        datoLeido = lecturaDatos(linea);
        if (datoLeido && datoLeido > 1) 
        {
            // Se calculan los factores y se imprimen
            tamanioArreglo = 30;
            arregloFactores = (uint64_t*) calloc(tamanioArreglo, sizeof(uint64_t));
            if (arregloFactores) 
            {
                arregloFactores = calcularFactores(datoLeido, arregloFactores, &tamanioArreglo);
                impresionDatos(datoLeido, arregloFactores, &tamanioArreglo);
                free(arregloFactores);
            }
        } 
        else if (datoLeido == NA) 
        {
            printf("%" PRId64 ": ", datoLeido); 
            printf("N.A \n");    
        }
        else 
        {
            printf("%" PRId64 ": ", datoLeido);
            printf("invalid number\n");
        }
    }
    return 0;
}
