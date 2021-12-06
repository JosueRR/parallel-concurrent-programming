/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class interface, which read numbers from stdin and prints the results
 * This class also calls the class calculator to factorize the received numbers
 */

#ifndef TAREAS_PRIMEFACT_OMP_MPI_SRC_MPI_CONTROL_H_
#define TAREAS_PRIMEFACT_OMP_MPI_SRC_MPI_CONTROL_H_
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <mpi.h>
#include <time.h>
#include "interface.h"
#include "calculator.h"
#include "dynamic_array.h"
#include "struct_array.h"
#include "thread_control.h"

/**
 * @brief Method which starts the different processes
 * @param argc is the number of arguments read from terminal
 * @param argv is the array with the arguments read
 * @return  1 if theres is any error
 */
int mpi_control_handle(int argc, char* argv[]);

/**
 * @brief Method to be runned by each process
 * @param threads_number number of threads tha will be used
 * @param process_count number of total processes created
 * @param process_number actual process
 * @return  1 if theres is any error
 */
int mpi_control_process_to_work(int process_number, uint64_t threads_number,
  int process_count);

/**
 * @brief Processes call this method to star factoring
 * @param my_work pointer to array with numbers to process
 * @param size of my_work array
 * @param threads_number number of threads tha will be used
 * @return  1 if theres is any error
 */
struct_array_t * mpi_control_star_work(int64_t * my_work, int size,
  uint64_t threads_number);

#endif  // TAREAS_PRIMEFACT_OMP_MPI_SRC_MPI_CONTROL_H_
