#include <mpi.h>
#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// DistributedExeption(process_number, exception_code, msg)
#define fail(msg) throw std::runtime_error(msg)

void greet(int process_number, int process_count, const char* process_hostname,
  std::vector<int64_t>test_array, const int size_array);

std::vector<int64_t> procedureSum(std::vector<int64_t>test_array, int process_count, const int size_array,
  const int process_start, const int process_finish, const char* process_hostname);

/* Maepo  */
int calculate_start(int rank, int end, int workers, int begin);
int calculate_finish(int rank, int end, int workers, int begin);


/* ENTRADA */
std::vector<int64_t> process_values(int process_number, int process_count
  , const char* process_hostname);


int main(int argc, char* argv[]) {
  // COSAS POR DEFAULT DE MPÍ
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int process_number = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

    int process_count = -1;
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);

    char process_hostname[MPI_MAX_PROCESSOR_NAME] = { '\0' };
    int hostname_length = -1;
    MPI_Get_processor_name(process_hostname, &hostname_length);

    try {
      /* ENTRADA */
      std::vector<int64_t> test_array;
      test_array = process_values(process_number, process_count, process_hostname);
      int const size_array = test_array.size();
      /* END ENTRADA */

      /* PROCESA ENTRADAS */
        /* MAPEO */
            std::cout << "Numero de proceso que opasa por aqui: " << process_number << std::endl;
            const int overall_start = 1;
            const int overall_finish = size_array;
              const int process_start = calculate_start(process_number, overall_finish, process_count, overall_start);
              const int process_finish = calculate_finish(process_number, overall_finish, process_count, overall_start);
            const int process_size = process_finish - process_start;
              #pragma omp parallel default(none) \
                shared(std::cout, process_hostname, process_number, process_start, process_finish)
              {
                int thread_start = -1;
                int thread_finish = -1;
                #pragma omp for schedule(static)
                for (int index = process_start; index < process_finish; ++index) {
                  if (thread_start == -1) {
                    thread_start = index;
                  }
                  thread_finish = index;
                }

                ++thread_finish;
                const int thread_size = thread_finish - thread_start;
                
                #pragma omp critical(can_print)
                std::cout << '\t' << process_hostname << ':' << process_number << '.'
                  << omp_get_thread_num() << ": range [" << thread_start << ", " <<
                  thread_finish << "[ size " << thread_size << std::endl;
              }

      //test_array = procedureSum(test_array, process_number, size_array, process_start, process_finish, process_hostname);
      /* END PROCESA ENTRADAS */
      
      /* PRINT RESULTS */
      greet(process_number, process_count, process_hostname, test_array, size_array);
      /* END PRINT RESULTS */

    } catch (const std::runtime_error& exception) {
      std::cerr << "error: " << exception.what() << std::endl;
      error = EXIT_FAILURE;
    }

    // /* MIERDA NECESARIA MAPEO */
    // const int overall_start = 0;
    // const int overall_finish = 20;

    /* Generar idef. procs. aleatorio */
      srand((unsigned)time(NULL)+process_number*process_count + hostname_length);
      int random_number = (rand() %(process_count - 0 + 1)) + 0;
      //std::cout << "El numero aleatorio es de: " << random_number << std::endl;
    /* End Generar idef. procs. aleatorio */

    /* MIERDA AGREAGADA DE HYBRID DIST */
    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
    error = EXIT_FAILURE;
  }
  return error;
}


// EQUIVALENTE AL PRINT
void greet(int process_number, int process_count, const char* process_hostname,
  std::vector<int64_t>test_array, const int size_array)
{
  const int previous_process = (process_count + process_number - 1)
    % process_count;
  const int next_process = (process_number + 1) % process_count;
  bool can_print = true;

  if (process_number > 0) {
    // receive(&can_print, 1, previous_process)
    if (MPI_Recv(&can_print, /*count*/ 1, MPI_C_BOOL, previous_process
      , /*tag*/ 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive message");
    }
  }

  printResult(arreglo);

  // send(can_print, 1, next_process);
  if (MPI_Send(&can_print, /*count*/ 1, MPI_C_BOOL, next_process, /*tag*/ 1
    , MPI_COMM_WORLD) != MPI_SUCCESS) {
    fail("could not send message");
  }
}


// EQUIVALENTE AL CALCULAR PARALELLO
std::vector<int64_t> procedureSum(std::vector<int64_t>test_array, int process_number, const int size_array,
  const int process_start, const int process_finish, const char* process_hostname) {
  std::vector<int64_t>sum_array;
  sum_array.resize(4);
  #pragma omp parallel for schedule(dynamic)
  for (size_t i = process_start; i < process_finish; i++) {
    sum_array[i] = test_array[i]*(5);
  }
  //return sum_array;


  #pragma omp parallel default(none) \
    shared(std::cout, process_hostname, process_number, process_start, process_finish)
  {
    int thread_start = -1;
    int thread_finish = -1;
    #pragma omp for schedule(static)
    for (int index = process_start; index < process_finish; ++index) {
      if (thread_start == -1) {
        thread_start = index;
      }
      thread_finish = index;
    }

    ++thread_finish;
    const int thread_size = thread_finish - thread_start;
    
    #pragma omp critical(can_print)
    std::cout << '\t' << process_hostname << ':' << process_number << '.'
      << omp_get_thread_num() << ": range [" << thread_start << ", " <<
      thread_finish << "[ size " << thread_size << std::endl;
  }
  return sum_array;
}


// MAPEO POR BLOQUE
int calculate_start(int rank, int end, int workers, int begin) {
  const int range = end - begin;
  return begin + rank * (range / workers) + std::min(rank, range % workers);
  // return begin + rank * (range / workers) + std::min(rank, range % workers);
}

int calculate_finish(int rank, int end, int workers, int begin) {
  return calculate_start(rank + 1, end, workers, begin);
}

/* MANEJA ENTRADA DE USUARIO */
std::vector<int64_t> process_values(int process_number, int process_count
  , const char* process_hostname) {
  std::vector<int64_t> values;
  size_t value_count = 0;

  if (process_number == 0) {
    int64_t value = 0.0;
    while (std::cin >> value) {
      values.push_back(value);
    }

    value_count = values.size();

    for (int target = 1; target < process_count; ++target) {
      static_assert(sizeof(value_count) == sizeof(uint64_t));
      if (MPI_Send(&value_count, /*count*/ 1, MPI_INT64_T, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("could not send value count");
      }
      if (MPI_Send(&values[0], value_count, MPI_INT64_T, target
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("could not send values");
      }
    }
  } else {
    if (MPI_Recv(&value_count, /*capacity*/ 1, MPI_INT64_T, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive value count");
    }

    values.resize(value_count);

    if (MPI_Recv(&values[0], /*capacity*/ value_count, MPI_INT64_T, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
      fail("could not receive values");
    }
  }

  //std::vector<int> sum_array = procedureSum(test_array, process_number, value_count);

  //greet(process_number, process_count, process_hostname, test_array, value_count);

  for (size_t index = 0; index < values.size(); ++index) {
    //test_array[index] = values[index];
    std::cout << process_hostname << ":" << process_number << ".m: values["
      << index << "] == " << values[index] << std::endl;
  }
  return values;
}
