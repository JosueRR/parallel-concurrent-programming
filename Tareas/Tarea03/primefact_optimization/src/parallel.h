/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef PARALLEL_H
#define PARALLEL_H
#include "prime_fact.h"
#include <pthread.h>

/* Structs */

/**
 @brief Datos compartidos entre hilos
 @param thread_count almacena la cantidad de hilos
 @param unit_count cantidad de entradas
 @param listaDatos arreglo de entradas
 @param next_unit siguiente unidad a ser comsumida
 @param consumed_count contador de entradas consumidas
 @param can_access_next_unit mutex para next_unit
 @param can_access_consumed_count mutex para consumed_count
*/
typedef struct shared_data {
  int64_t thread_count;
  int64_t unit_count;
  int64_t next_unit;
  int64_t consumed_count;
  pthread_mutex_t can_access_next_unit;
  pthread_mutex_t can_access_consumed_count;
  EstructuraArreglo listaDatos;
} shared_data_t;

/**
 @brief Datos privados de los hilos
 @param thread_number identificador de número de hilo
 @param my_unit indice en el cual debe trabajar el hilo
 @param shared_data puntero a la memoria compartida entre hilos
*/
typedef struct private_data {
  int64_t thread_number;
  int64_t my_unit;
  shared_data_t* shared_data;
} private_data_t;


/**
 @brief Setea la cantidad de hilos e invoca la rutina que los ejecuta
 @param argc argumento del usuario indica cantidad de hilos
 @param argv argumento del usuario indica cantidad de hilos
 @param arreglo representa el arreglo de entradas
*/
void initParalelizador(int argc, char* argv[], EstructuraArreglo arreglo);

/**
 @brief Reparte indices a hilos según lleguen
 @param shared_data datos compartidos entre hilos
 @param shared_data datos privados de los hilos
*/
void repartirTareas(shared_data_t* shared_data, private_data_t* private_data);

/**
 @brief Crea los hilos y los ejecuta
 @param shared_data datos compartidos entre hilos
*/
void createThreads(shared_data_t* shared_data);

/**
 @brief Calcula los factores de forma paralela dado un número
 @param data datos del hilos
*/
void* calcularParallel(void* data);

#endif  // PARALLEL_H
