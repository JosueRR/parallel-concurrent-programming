/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Contiene y define lo que compone la clase
*/

#ifndef PARALLEL_H
#define PARALLEL_H
#include <omp.h>
#include <unistd.h>
#include "prime_fact.h"

/**
 @brief Asigna la cantidad de hilos y calcula de forma paralela
 @param argc argumento del usuario indica cantidad de hilos
 @param argv argumento del usuario indica cantidad de hilos
 @param listaEntrada representa el arreglo de entradas
*/
void calcParallel(int argc, char* argv[], EstructuraArreglo *listaEntrada);

#endif  // PARALLEL_H
