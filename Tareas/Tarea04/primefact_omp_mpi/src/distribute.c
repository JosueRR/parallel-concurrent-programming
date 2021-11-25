/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Implementación de las subrutinas
*/

#include <distribute.h>
#include <omp.h>
#include <mpi.h>

void distribute_init(int argc, char* argv[]) {
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
        int process_number = -1;
        MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

        int process_count = -1;
        MPI_Comm_size(MPI_COMM_WORLD, &process_count);

        char process_hostname[MPI_MAX_PROCESSOR_NAME];
        int hostname_length = -1;
        MPI_Get_processor_name(process_hostname, &hostname_length);

        // Procesa la entrada del usuario
        EstructuraArreglo listaEntrada;
        process_values(process_number, process_count);

        // Sets de índices
        const int overall_start = 0;
        const int overall_finish = listaEntrada.usado;
        const int process_start = calculate_start(process_number,
            overall_finish, process_count, overall_start);
        const int process_finish = calculate_finish(process_number,
            overall_finish, process_count, overall_start);

        // Set cantidad de hilos
        int thread_count = omp_get_max_threads();
        if (argc >= 2) {
            if (sscanf(argv[1], "%i", &thread_count) == 1) {
            } else {
            fprintf(stderr, "Error: invalid thread count\n");
            }
        }
        // Calcula número primos de forma paralela
        #pragma omp parallel for \
        schedule(dynamic) \
        num_threads(thread_count) \
        default(none) shared(listaEntrada, process_start, process_finish)
        for (int index = process_start; index < process_finish; index++) {
            calcularFactores(&listaEntrada.arreglo[index]);
        }
        // Print de los resultados
        print_result(process_number, process_count, listaEntrada);
        MPI_Finalize();
    } else {
        printf("error: could not init MPI\n");
    }
}

void process_values(int process_number, int process_count) {
    int64_t array_lenght = 0;
    char* elements[BLOCK_SIZE];
    if (process_number == 0) {
      FILE* entrada = stdin;
      EstructuraArreglo arreglo;
      initArray(&arreglo, BLOCK_SIZE);
      arreglo = lecturaDatos(entrada, arreglo);
      array_lenght = arreglo.usado;
      for (int64_t i = 0; i < array_lenght; i++) {
          elements[i] = arreglo.arreglo[i].charIngreso;
      }
      for (int i = 0; i < process_count; i++) {
        if (MPI_Send(elements, /*capacity*/ array_lenght, MPI_CHAR, /*source*/ i
        , /*tag*/ 0, MPI_COMM_WORLD) != MPI_SUCCESS) {
          printf("Error could send input");
        }
      }
    } else {
       MPI_Recv(&elements[0], /*capacity*/ array_lenght, MPI_CHAR, /*source*/ 0
      , /*tag*/ 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
}

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
