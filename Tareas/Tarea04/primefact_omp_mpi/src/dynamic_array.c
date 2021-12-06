/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class calculator which calculates the prime factoring of any positive integer
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "dynamic_array.h"

/**
 * @brief Increases amount of memory allocated
 * @param array pointer to object to modify
 * @return 1 if there is any error. Otherwise returns 0
*/
int64_t dynamic_array_increase_capacity(dynamic_array_t* array);

int64_t dynamic_array_init(dynamic_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void dynamic_array_destroy(dynamic_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int64_t dynamic_array_append(dynamic_array_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (dynamic_array_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int64_t dynamic_array_increase_capacity(dynamic_array_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)  //NOLINT
    realloc(array->elements, new_capacity * sizeof(int64_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
