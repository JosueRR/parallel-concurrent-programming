/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class calculator which calculates the prime factoring of any positive integer
 */

#ifndef TAREAS_PRIMEFACT_OMP_MPI_SRC_DYNAMIC_ARRAY_H_
#define TAREAS_PRIMEFACT_OMP_MPI_SRC_DYNAMIC_ARRAY_H_
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Registro que representa un arreglo dinámico que contiene elementos dinámico tipo int64_t.
 * 
 */
typedef struct {
  int64_t capacity;
  int64_t count;
  int64_t* elements;
} dynamic_array_t;

/**
 * @brief Inits dynamic array
 * @param array Pointer to object to initialize
 * @return 1 if there is any error. Otherwise returns 0
 */
int64_t dynamic_array_init(dynamic_array_t* array);

/**
 * @brief Destructor
 * @param array Pointer to object to destroy
 * @return 1 if there is any error. Otherwise returns 0
 */
void dynamic_array_destroy(dynamic_array_t* array);

/**
 * @brief Push a new element to the array
 * @param array pointer to object to modify
 * @param element Arrays add integers of 64 bits
 * @return 1 if there is any error. Otherwise returns 0
 */
int64_t dynamic_array_append(dynamic_array_t* array, int64_t element);

#endif  // TAREAS_PRIMEFACT_OMP_MPI_SRC_DYNAMIC_ARRAY_H_
