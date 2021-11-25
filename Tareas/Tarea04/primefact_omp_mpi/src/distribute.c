/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include <distribute.h>
#include <omp.h>
#include <mpi.h>



int calculate_start(int rank, int end, int workers, int begin) {
  const int range = end - begin;
  int min = range % workers;
  if (rank < min) {
      min = rank;
  }
  return begin + rank * (range / workers) + min;
}

int calculate_finish(int rank, int end, int workers, int begin) {
  return calculate_start(rank + 1, end, workers, begin);
}
