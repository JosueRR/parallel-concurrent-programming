/*
 * Copyright 2021 Josue Retana  - UCR
 * Header file of class interface which read numbers from stdin and prints the results
 */

#ifndef TAREAS_PRIMEFACT_PTHREAD_SRC_INTERFACE_H_
#define TAREAS_PRIMEFACT_PTHREAD_SRC_INTERFACE_H_
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

// #include "queue_data.h"
#include "calculator.h"
#include "dynamic_array.h"
#include "struct_array.h"


/** @brief this method checks if the arguments received are valid
 * @param argc is the number of arguments read from terminal
 * @param argv is the array with the arguments read
 * @return the number total of threads that the user wants to use
 */
uint64_t interface_validate_args(int argc, char* argv[]);

int interface_process_to_work(int process_number);

/** @brief Method to recollect numbers from the input stream
 * @param data pointer to a data structure of type queue where the input numbers are stored
 * @return Integer containing a 1 if there was any error. If not 0 is returned
 */
int interface_get_data(dynamic_array_t * data);

/** @brief Simple method to ignore one line from the input stream
 * @code 
  char ignore = '\0';
  while (ignore != EOF && ignore != '\n') {
    ignore = fgetc(stdin);
  }
 * @endcode
 */
void ignore_line();

/** @brief Checks if the number read from the stream is valid
 * @details Only checks if the value is within the range of an 64 bits integer 
 * @param is_invalid pointer to variable where the result of the validation will be stored
 * * @code 
  if (errno == ERANGE) {
    *is_invalid = 1;
    clearerr(stdin);
    errno = 0;
  }
 * @endcode 'ERANGE' constant means there was an "out of range error"
 * @remark 
 */
void interface_validate_data(int64_t * is_invalid);


/** @brief Method to print the result of the program
 * @param data pointer to the queue which contains all numbers and their respective prime factorization
 */
void interface_print_data(struct_array_t * data);

#endif  // TAREAS_PRIMEFACT_PTHREAD_SRC_INTERFACE_H_
