/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class calculator which calculates the prime factoring of any positive integer
 */

#ifndef TAREAS_PRIMEFACT_OMP_MPI_SRC_STRUCT_ARRAY_H_
#define TAREAS_PRIMEFACT_OMP_MPI_SRC_STRUCT_ARRAY_H_
#include <stddef.h>
#include <stdint.h>
#include "queue_data.h"

/**
 * @brief Registro para almacenar los numero a procesar y la cola de su factorizacion
 * 
 */
typedef struct {
  int64_t number;
  int is_invalid;
  queue_data_t * primefact;
} array_node_t;


/**
 * @brief Registro que representa un arreglo dinámico que contiene elementos dinámico tipo int64_t.
 * 
 */
typedef struct {
  int64_t capacity;
  int64_t count;
  array_node_t* elements;
} struct_array_t;

/**
 * @brief Inits dynamic array
 * @param array Pointer to object to initialize
 * @return 1 if there is any error. Otherwise returns 0
 */
int64_t struct_array_init(struct_array_t* array);

/**
 * @brief Destructor
 * @param array Pointer to object to destroy
 * @return 1 if there is any error. Otherwise returns 0
 */
void struct_array_destroy(struct_array_t* array);

/**
 * @brief Push a new element to the array
 * @param array pointer to object to modify
 * @param number number to append
 * @param is_invalid bool of validity of the number
 * @return 1 if there is any error. Otherwise returns 0
 */
int64_t struct_array_append(struct_array_t* array, int64_t number,
  int is_invalid);

#endif  // TAREAS_PRIMEFACT_OMP_MPI_SRC_STRUCT_ARRAY_H_
