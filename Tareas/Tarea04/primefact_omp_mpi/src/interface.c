/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class interface, which read numbers from stdin and prints the results
 * This class also calls the class calculator to factorize the received numbers
 */
#include "interface.h"

uint64_t interface_validate_args(int argc, char* argv[]) {
  int64_t total_threads = sysconf(_SC_NPROCESSORS_ONLN);
  // we read a signed int in order to detect negative numbers
  if (argc == 2) {
    if (sscanf(argv[1], "%ld", &total_threads) == 0 || total_threads < 1
     || errno == ERANGE) {
      if (errno) {
        fprintf(stderr, "ERROR: too many threads\n");
      } else {
        total_threads = sysconf(_SC_NPROCESSORS_ONLN);
        fprintf(stderr,
         "Number of threads has to be a positive integer.\n");
        fprintf(stderr,
         "The number of proccessors available [%ld] are going to be used.\n",
         total_threads);
      }
    }
  }
  return (uint64_t) total_threads;
}

int interface_get_data(dynamic_array_t * data) {
  int64_t current_value = 0;
  int error = EXIT_SUCCESS;

  // set to 1 if there is a out of range or a string was read from the input
  int64_t is_invalid = 0;
  errno = 0;
  // the loop continues while the end of file (eof) hasn't been reached
  // while (!eof):
  while (feof(stdin) == 0) {
    if (fscanf(stdin, "%"SCNd64, &current_value) == 1) {
      // we check if the end_of_file wasn't read
      // this way we avoid to add the ctrl+d/end_of_file to the queue
      interface_validate_data(&is_invalid);
      if (is_invalid == 2) {
        current_value = 0;
        is_invalid = 1;
      }
      if (current_value < 0) {
        is_invalid = 1;
      }
      dynamic_array_append(data, is_invalid);
      dynamic_array_append(data, current_value);
      is_invalid = 0;
    } else {
      // else statement means that the scan couldn't
      // read one integer from the input stream
      // so we ignore the next characters until the next \n
      ignore_line();
      current_value = 0;
      dynamic_array_append(data, 1);
      dynamic_array_append(data, 0);
    }
    current_value = 0;
  }
  if (data->count - 2 == 0) {
    return EXIT_FAILURE;
  }
  return error;
}

void ignore_line() {
  // this is a simple method wich ingores any character
  // from the input stream until the next line
  char ignore = '\0';
  while (ignore != EOF && ignore != '\n') {
    ignore = fgetc(stdin);
  }
}

void interface_validate_data(int64_t * is_invalid) {
  if (errno) {
    // if errno variable == ERANGE means there was a out of range error
    *is_invalid = 2;
    clearerr(stdin);
    errno = 0;
  }
}

void interface_print_data(struct_array_t * data) {
  int64_t temp = 0;
  int is_invalid = 0;
  queue_data_t * fact = 0;
  queue_node_t * current = 0;
  int64_t exponent = 0;

  for (int i = 0; i < data->count; ++i) {
    temp = data->elements[i].number;
    is_invalid = data->elements[i].is_invalid;
    if (is_invalid) {
      if (temp < 0) {
        printf("%ld: invalid number", temp);
      } else {
        printf("invalid number");
      }
    } else {
      printf("%ld:", temp);
      if (temp ==0 || temp == 1) {
        printf(" NA");
      } else {
        fact = data->elements[i].primefact;
        current = fact->head;
        while (current) {
          printf(" %ld", queue_node_get_element(current));
          exponent = queue_node_get_element_counter(current);
          if (exponent > 1) {
            printf("^%ld", exponent);
          }
          current = queue_node_get_next(current);
        }
      }
    }
    printf("\n");
  }
}
