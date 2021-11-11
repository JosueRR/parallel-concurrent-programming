#include <omp.h>
#include <iostream>
using namespace std;

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

    // default...private()

    #pragma omp parallel num_threads(thread_count) \
    default(none) shared(iteration_count, cout)
    {
        // Stage 1
        #pragma omp for
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            #pragma omp critical
            cout << "Stage 1: " << omp_get_thread_num() << '/' 
            << omp_get_num_threads() << ": iteration " << iteration << '/'
            << iteration_count << endl;
        }

        #pragma omp single
        cout << endl;
        //#pragma omp barrier
        
        // Stage 2
        #pragma omp for
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            #pragma omp critical
            cout << "Stage 2: " << omp_get_thread_num() << '/' 
            << omp_get_num_threads()
            << ": iteration " << iteration << '/' << iteration_count << endl;
        }

        #pragma omp single
        cout << endl;
        //#pragma omp barrier

        // Stage 3
        #pragma omp for
        for (int iteration = 0; iteration < iteration_count; ++iteration) {
            #pragma omp critical
            cout << "Stage 3: " << omp_get_thread_num() << '/' 
            << omp_get_num_threads()
            << ": iteration " << iteration << '/' << iteration_count << endl;
        }
    }
}