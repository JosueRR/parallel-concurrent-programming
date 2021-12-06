/*
 * Copyright 2021 Josue Retana  - UCR
 * Header file of class Thread_control
 */

#ifndef TAREAS_PRIMEFACT_PTHREAD_SRC_THREAD_CONTROL_H_
#define TAREAS_PRIMEFACT_PTHREAD_SRC_THREAD_CONTROL_H_
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include "queue_data.h"
#include "calculator.h"
#include "struct_array.h"
#include "interface.h"


/** @brief Create and start threads
 * @param data pointer to queue which contains all data
 * @param total_threads number of threads tha will be used
 * @return 0 if there isn't any error
 */
int threads_to_work(struct_array_t * data, uint64_t total_threads);

/** @brief Method that calculates the real quantity of threads needed
 * @details This method will check hoy many valid numbers there are in the queue
 * @param data pointer to shared data struct which contains the number to factorize
 * @remark This method will be called only if the amount of numbers to process 
 * is less than te number of threads that the user selected
 * @return number of threads to create
 */
uint64_t threads_control_calculate_workload(struct_array_t * data);

#endif  // TAREAS_PRIMEFACT_PTHREAD_SRC_THREAD_CONTROL_H_
