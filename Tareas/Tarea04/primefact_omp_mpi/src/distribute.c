/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include <distribute.h>
#include <omp.h>
#include <mpi.h>


void print_result(int process_number, int process_count,
EstructuraArreglo arreglo) {
    const int previous_process = (process_count + process_number - 1)
        % process_count;
    const int next_process = (process_number + 1) % process_count;
    bool can_print = true;
    if (process_number > 0) {
        // receive(&can_print, 1, previous_process)
        if (MPI_Recv(&can_print, /*count*/ 1, MPI_C_BOOL, previous_process
        , /*tag*/ 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
        printf("could not receive message\n");
        }
    }
    printResult(arreglo);
    // send(can_print, 1, next_process);
    if (MPI_Send(&can_print, /*count*/ 1, MPI_C_BOOL, next_process, /*tag*/ 1
        , MPI_COMM_WORLD) != MPI_SUCCESS) {
        printf("could not send message\n");
    }
}

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
