/*
*   Copyright 2021 Josue Retana  - UCR
 * Implementation file of class calculator which calculates the prime factoring of any positive integer
 */

#include "calculator.h"

int calculator_factorize_data(struct_array_t * data, uint64_t total_threads) {
  int error = EXIT_SUCCESS;

  if (data) {
    error = threads_to_work(data, total_threads);

  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

int calculator_factorize_number(int64_t value, queue_data_t * primefact) {
  int error = EXIT_SUCCESS;

  while (value % 2 == 0) {
    error = queue_data_insert(primefact, 2);
    value >>= 1;
  }

  for (int64_t i = 3; i <= sqrt((double) value); i = i + 2) {  //NOLINT
    while (value % i == 0) {
      error = queue_data_insert(primefact, i);
      value /= i;
    }
  }

  if (value > 2) {
    error = queue_data_insert(primefact, value);
  }

  return error;
}
