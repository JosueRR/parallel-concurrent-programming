#include <omp.h>
#include <iostream>
#include <vector>
using namespace std;

void print_mapping(const char* type, const vector<int> &mapping);

int main(int argc, char* argv[]) {
    // Amount of threads
    int thread_count = omp_get_max_threads();
    if (argc >= 2) {
        thread_count = atoi(argv[1]);
    }

    // Amount of iterations
    int iteration_count = thread_count;
    if (argc >= 3) {
        iteration_count = atoi(argv[2]);
    }

    // Size of block mapping
    int block_size = 0;
    if (argc >= 4) {
        block_size = atoi(argv[3]);
    }
    (void)block_size;

    vector<int> mapping(iteration_count);

    // default...private()
    #pragma omp parallel num_threads(thread_count) \
    default(none) shared(iteration_count, cout, mapping)
    {
        #pragma omp for schedule(static)
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            mapping[iteration] = omp_get_thread_num();
        }
        #pragma omp single
        print_mapping("static   ", mapping);

        #pragma omp for schedule(dynamic)
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            mapping[iteration] = omp_get_thread_num();
        }
        #pragma omp single
        print_mapping("dinamyc   ", mapping);

        #pragma omp for schedule(guided)
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            mapping[iteration] = omp_get_thread_num();
        }
        #pragma omp single
        print_mapping("guided   ", mapping);
    }
}

void print_mapping(const char* type, const vector<int> &mapping) {
    cout << type;
    for (size_t index = 0; index < mapping.size(); index++) {
        cout << mapping[index] << (index == mapping.size() - 1 ? '\n' : ' ');
    }
}

