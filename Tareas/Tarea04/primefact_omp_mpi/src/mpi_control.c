/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of class interface, which read numbers from stdin and prints the results
 * This class also calls the class calculator to factorize the received numbers
 */
#include "mpi_control.h"

/**
 * @brief Method to shuffle an array
 * @param array pointer to array to shuffle
 * @param size of the array
 * @return  1 if theres is any error
 */
void mpi_control_shuffle(int * array, int size);

/**
 * @brief Method to creat unit of work
 * @param array_length pointer to array to shuffle
 * @param total_process number of total process
 * @return pointer to array of blocks
 */
int64_t * mpi_control_create_blocks(int64_t array_length, int total_process);

/**
 * @brief Method to creat unit of work
 * @param rank number of process
 * @param end end of array to disrtribute
 * @param workers number od processes
 * @param begin begin of array to disrtribute
 * @return pointer to array of blocks
 */
int mpi_control_calculate_start(int rank, int end, int workers, int begin);

/**
 * @brief Method to creat unit of work
 * @param rank number of process
 * @param end end of array to disrtribute
 * @param workers number od processes
 * @param begin begin of array to disrtribute
 * @return pointer to array of blocks
 */
int mpi_control_calculate_finish(int rank, int end, int workers, int begin);

/**
 * @brief Calculates minimum number between to numbers
 * @param x first number to comparate
 * @param y second number to comparate
 * @return minimum number
 */
int64_t mpi_control_min(int64_t x, int64_t y);

/**
 * @brief Send messages to indicate which process has to print
 * @param process_array array of processes
 * @param process_count total number of processes
 * @param my_values array of values of process 0
 */
void send_print_messages(int * process_array, int process_count,
  struct_array_t * my_values);

/**
 * @brief Process prints if message to print is received
 * @param my_values array of values of process 0
 */
void print_results(struct_array_t * my_values);

/**
 * @brief This methods sends work load to the processes
 * @param array_blocks array of blocks
 * @param process_count total number of processes
 * @param first_index first index to process
 * @param last_index last index to process
 * @param data dynamic array with the inputs
 * @return pointer to array with indexes per unit
 */
int * distribute_work(int64_t * array_blocks,
  int process_count,
  int * first_index,
  int * last_index,
  dynamic_array_t * data);

/**
 * @brief This methods sends data to other processes
 * @param process_number actual process
 * @param first_index first index to process
 * @param last_index last index to process
 * @param data dynamic array with the inputs
 */
void send_data(int process_number,
  int first_index,
  int last_index,
  dynamic_array_t * data);

/**
 * @brief Method to receive first and last index
 * @param process_number actual process
 * @param first_index first index to process
 * @param last_index last index to process
 */
void receive_indexes(int process_number,
  int * first_index,
  int * last_index);

/**
 * @brief Method to receive the array to process
 * @param my_work array of blocks
 * @param size size to receive
 * @param process_number number of actual process
 */
void receive_array(int64_t * my_work, int size, int process_number);

int mpi_control_handle(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;

  uint64_t total_threads = interface_validate_args(argc, argv);
  double start_time = 0;
  int ignore = 0;
  if (MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED,
    &ignore) == MPI_SUCCESS) {
    int process_number = -1;
    error = MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    error =  MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    error = MPI_Get_processor_name(process_hostname, &hostname_length);
    if (process_number == 0) {
      start_time = MPI_Wtime();
    }
    // code
    if (!error) {
      error = mpi_control_process_to_work(process_number, total_threads,
        process_count);
    }

    if (process_number == 0) {
      fprintf(stderr, "elapsed time: %lf\n" ,  MPI_Wtime() - start_time);
    }
    MPI_Finalize();
  } else {
    fprintf(stderr, "ERROR: could not init MPI");
    error = EXIT_FAILURE;
  }
  return error;
}

int mpi_control_process_to_work(int process_number, uint64_t threads_number,
  int process_count) {
  int error = EXIT_SUCCESS;
  int first_index = 0;
  int last_index = 0;
  int64_t * my_work = 0;
  int * process_array = 0;
  if (process_number == 0) {
    dynamic_array_t data;
    error = dynamic_array_init(&data);
    // we read from stdin
    error = interface_get_data(&data);
    int64_t * array_blocks =
    mpi_control_create_blocks(data.count - 2, process_count);
    if (array_blocks) {
      process_array = distribute_work(array_blocks, process_count,
        &first_index, &last_index, &data);
      int size = last_index - first_index;
      my_work = (int64_t *) calloc(size, sizeof(int64_t));  // NOLINT
      int counter = 0;
      for (int i = first_index; i < last_index ; ++i) {
        my_work[counter++] = data.elements[i];
      }
      free(array_blocks);
    }
    dynamic_array_destroy(&data);
  } else {
    receive_indexes(process_number, &first_index, &last_index);
    int size = last_index - first_index;
    if (size) {
      my_work = (int64_t *) malloc(size * sizeof(int64_t));  //NOLINT
      receive_array(my_work, size, process_number);
    }
  }
  if (my_work) {
    int size = last_index - first_index;
    struct_array_t * my_values =
      mpi_control_star_work(my_work, size, threads_number);
    if (!process_number) {
      send_print_messages(process_array, process_count, my_values);
      free(process_array);
    } else {
      print_results(my_values);
    }
    free(my_work);
    struct_array_destroy(my_values);
  }
  return error;
}

void send_print_messages(int * process_array, int process_count,
  struct_array_t * my_values ) {
  int can_print = 1;
  int can_continue = 0;
  int target = 0;
  for (int i = 0; i < process_count; ++i) {
    target = process_array[i];
    if (target) {
      MPI_Send(&can_print, 1, MPI_C_BOOL, target, 0, MPI_COMM_WORLD);
      MPI_Recv(&can_continue, 1,
        MPI_C_BOOL, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
      interface_print_data(my_values);
    }
  }
}

void print_results(struct_array_t * my_values) {
  int can_print = 1;
  int can_continue = 0;
  MPI_Recv(&can_print, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  interface_print_data(my_values);
  MPI_Send(&can_continue, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD);
}

int * distribute_work(int64_t * array_blocks,
  int process_count,
  int * first_index,
  int * last_index,
  dynamic_array_t * data) {
  int * process_array = calloc(process_count, sizeof(int));
  for (int i = 0; i < process_count; ++i) {
    process_array[i] = i;
  }
  mpi_control_shuffle(process_array, process_count);
  int counter = 0;
  for (int i = 0; i < process_count; ++i) {
    if (process_array[i] != 0) {
      send_data(process_array[i], array_blocks[counter],
        array_blocks[counter+1], data);
      counter += 2;
    } else {
      *first_index  = array_blocks[counter++];
      *last_index = array_blocks[counter++];
    }
  }
  return process_array;
}

void send_data(int process_number,
  int first_index,
  int last_index,
  dynamic_array_t * data) {
  // sending first index
  if (MPI_Send(&first_index, 1, MPI_INT64_T, process_number, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    fprintf(stderr, "ERROR: could not send first index %i", process_number);
  }
  // sending last index
  if (MPI_Send(&last_index, 1, MPI_INT64_T, process_number, 0,
    MPI_COMM_WORLD) != MPI_SUCCESS) {
    fprintf(stderr, "ERROR: could not send last index %i", process_number);
  }

  int size = last_index - first_index;
  if (size) {
    int64_t * my_work = (int64_t *) calloc(size, sizeof(int64_t));  // NOLINT
    int counter = 0;
    for (int i = first_index; i < last_index ; ++i) {
      my_work[counter++] = data->elements[i];
    }
    // sending values to process
    if (MPI_Send(my_work, size, MPI_INT64_T, process_number, 0,
      MPI_COMM_WORLD) != MPI_SUCCESS) {
      fprintf(stderr, "ERROR: could not send values array %i", process_number);
    }
    free(my_work);
  }
}

void receive_indexes(int process_number,
  int * first_index,
  int * last_index) {
  // receiving first index
  if (MPI_Recv(first_index, 1, MPI_INT64_T, 0, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    fprintf(stderr, "ERROR: could not receive first index  %i", process_number);
  }

  // receiving last index
  if (MPI_Recv(last_index, 1, MPI_INT64_T, 0, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    fprintf(stderr, "ERROR: could not receive last index  %i", process_number);
  }
}

void receive_array(int64_t * my_work, int size, int process_number) {
  // receiving last index
  if (MPI_Recv(my_work, size, MPI_INT64_T, 0, 0,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
    fprintf(stderr, "ERROR: could not receive last index  %i", process_number);
  }
}

int64_t * mpi_control_create_blocks(int64_t array_length, int total_process) {
  int64_t * blocks_array = 0;
  if (array_length > 0) {
    int size = total_process << 1;
    blocks_array = (int64_t *) calloc(size, sizeof(int64_t));  // NOLINT
    int process_to_distribute = total_process;
    if ((array_length>>1) < total_process) {
      process_to_distribute = array_length>>1;
    }
    int counter = 0;
    // creation of blocks
    for (int i = 0; i < process_to_distribute; ++i) {
      blocks_array[counter++] =
        mpi_control_calculate_start(i, array_length, process_to_distribute, 0);
      blocks_array[counter++] =
        mpi_control_calculate_finish(i, array_length, process_to_distribute, 0);
    }
  }
  return blocks_array;
}

struct_array_t * mpi_control_star_work(int64_t * my_work, int size,
  uint64_t threads_number) {
  struct_array_t * my_values =
    (struct_array_t *) calloc(1, sizeof(struct_array_t));  //NOLINT
  struct_array_init(my_values);
  for (int i = 0; i < size; i += 2) {
    struct_array_append(my_values, my_work[i+1], my_work[i]);
  }
  calculator_factorize_data(my_values, threads_number);
  return my_values;
}


int mpi_control_calculate_start(int rank, int end, int workers, int begin) {
const int range = end - begin;
  int temp = begin + rank * (range / workers)
      + mpi_control_min(rank, range % workers);
  return temp % 2? temp+1 : temp;
}

int mpi_control_calculate_finish(int rank, int end, int workers, int begin) {
  int temp = mpi_control_calculate_start(rank + 1, end, workers, begin);
  return temp % 2? temp+1 : temp;
}

int64_t mpi_control_min(int64_t x, int64_t y) {
  return ((x < y) ? x : y);
}

void mpi_control_shuffle(int * array, int size) {
  srand(time(NULL));
  if (size > 1) {
    for (int i = 0; i < size - 1; ++i) {
      int j = i + rand() / (RAND_MAX / (size - i) + 1);  // NOLINT
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}
