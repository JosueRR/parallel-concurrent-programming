/*
 * Copyright 2021 Josue Retana  - UCR
 * Header file of class calculator which calculates the prime factoring of any positive integer
 */

#ifndef TAREAS_PRIMEFACT_PTHREAD_SRC_CALCULATOR_H_
#define TAREAS_PRIMEFACT_PTHREAD_SRC_CALCULATOR_H_
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "queue_data.h"
#include "thread_control.h"
#include "struct_array.h"


/** @brief Factorizes all received data
 * @details This function loops trough the data queue and factorize each number
 * @param data pointer which contains the data to factorize
 * @param total_threads number of threads that are going to be used
 * @remark The result of each number is stored in the same queue
 * @return It return a 1 if there was any error during the process
 */
int calculator_factorize_data(struct_array_t * data, uint64_t total_threads);

/** @brief Factorizes a given number
 * @details This algorithm is based on "https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/"
 * which uses the eratosthenes sieve algorithm
 * @param primefact queue which is the pointer to the queue where the result will be stored
 * @param value to factorize at the moment
 * @remark The result of each number is stored in the queue prime_fact which comes from each node of the queue data
 * @return It return a 1 if there was any error trying to append a factor to the queue
 */
int calculator_factorize_number(int64_t value, queue_data_t * primefact);

#endif  // TAREAS_PRIMEFACT_PTHREAD_SRC_CALCULATOR_H_
