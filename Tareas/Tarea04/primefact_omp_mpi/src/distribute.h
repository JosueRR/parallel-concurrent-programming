/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef DISTRIBUTE_H
#define DISTRIBUTE_H
#include "prime_fact.h"

/**
 @brief El proceso 0 lee ingresos de la entrada estándar y
 la envía a los demás procesos
 @param process_hostname nombre del host
 @param process_count contador de procesos
 @param process_number número del proceso
*/
void distribute_init(int argc, char* argv[]);

/**
 @brief El proceso 0 lee ingresos de la entrada estándar y
 la envía a los demás procesos
 @param process_hostname nombre del host
 @param process_count contador de procesos
 @param process_number número del proceso
*/
void process_values(int process_number, int process_count);

/**
 @brief El proceso imprime el resultado de los números procesados
 @param process_count contador de procesos
 @param process_number número del proceso
 @param arreglo arreglo de entradas del usuario
*/
void print_result(int process_number, int process_count,
EstructuraArreglo arreglo);

/**
 @brief calcula el índice inicial sobre el cuál iterar
 @param rank número de proceso
 @param end índice final del arreglo
 @param workers cantidad de procesos
 @param begin índice inicial del arreglo
 @return índice incial sobre el que debería empezar a 
  procesar el arreglo de entrada
 */
  int calculate_start(int rank, int end, int workers, int begin);

/**
 @brief calcula el índice inicial sobre el cuál iterar
 @param rank número de proceso
 @param end índice final del arreglo
 @param workers cantidad de procesos
 @param begin índice inicial del arreglo
 @return índice final sobre el que debería terminar de 
  procesar el arreglo de entrada
 */
  int calculate_finish(int rank, int end, int workers, int begin);
#endif  // DISTRIBUTE_H
