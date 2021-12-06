/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation of class Thread_control
 */

#include"thread_control.h"

int threads_to_work(struct_array_t* data, uint64_t total_threads) {
  int error = EXIT_SUCCESS;

  // if (data.size < total_threads) do:
  if ((int) total_threads > data->count) {  // NOLINT
    // then we create only the necessary threads which is the size of queue_data
    total_threads = threads_control_calculate_workload(data);
  }

  #pragma omp parallel for schedule(dynamic) num_threads(total_threads) \
    default(none) shared(data)
  for (int64_t i = 0; i < data->count; ++i) {
    if (data->elements[i].number > 1 &&
      !(data->elements[i].is_invalid)) {
      calculator_factorize_number(data->elements[i].number,
        data->elements[i].primefact);
    }
  }
  return error;
}

uint64_t threads_control_calculate_workload(struct_array_t * data) {
  uint64_t total_threads = 0;
  for (int i = 0; i < data->count; ++i) {
    if (!data->elements[i].is_invalid &&
      data->elements[i].number > 1) {
      ++total_threads;
    }
  }
  return total_threads;
}
