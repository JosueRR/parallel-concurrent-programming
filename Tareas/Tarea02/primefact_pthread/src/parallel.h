/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef PARALLEL_H
#define PARALLEL_H
#include "prime_fact.h"

/* Structs */

/**
 @brief Datos compartidos entre hilos
 @param thread_count almacena la cantidad de hilos
 @param listaDatos arreglo de entradas
*/
typedef struct shared_data {
  int64_t thread_count;
  EstructuraArreglo listaDatos;
} shared_data_t;

/**
 @brief Datos privados de los hilos
 @param tieneTrabajo indica si el hilos tiene trabajo por hacer
 @param indiceBase indice del inicio del rango sobre el cual debe trabajar el hilo
 @param indiceFinal indice del final del rango sobre el cual debe trabajar el hilo
 @param shared_data puntero a la memoria compartida entre hilos
*/
typedef struct private_data {
  bool tieneTrabajo;
  int64_t indiceBase;
  int64_t indiceFinal;
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
 @brief Reparte los números entre la cantidad de hilos
 @param shared_data datos compartidos entre hilos
 @param private_data datos privados de los hilos
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