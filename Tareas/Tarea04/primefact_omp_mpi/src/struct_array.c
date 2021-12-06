/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class calculator which calculates the prime factoring of any positive integer
 */
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "struct_array.h"

/**
 * @brief Increases amount of memory allocated
 * @param array pointer to object to modify
 * @return 1 if there is any error. Otherwise returns 0
*/
int64_t struct_array_increase_capacity(struct_array_t* array);

int64_t struct_array_init(struct_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void struct_array_destroy(struct_array_t* array) {
  assert(array);
  for (int i = 0; i < array->count; ++i) {
    queue_data_destroy(array->elements[i].primefact);
  }
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int64_t struct_array_append(struct_array_t* array,
  int64_t number, int is_invalid) {
  assert(array);
  if (array->count == array->capacity) {
    if (struct_array_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  int position = array->count++;
  array->elements[position].number = number;
  array->elements[position].is_invalid = is_invalid;
  array->elements[position].primefact =
    (queue_data_t *) calloc(1, sizeof(queue_data_t));  //NOLINT
  queue_data_init(array->elements[position].primefact);
  return EXIT_SUCCESS;
}

int64_t struct_array_increase_capacity(struct_array_t* array) {
  size_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  array_node_t* new_elements = (array_node_t*)  //NOLINT
    realloc(array->elements, new_capacity * sizeof(array_node_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
