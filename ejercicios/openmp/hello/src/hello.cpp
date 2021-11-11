#include <iostream>
using namespace std;

int main() {
    #pragma omp parallel
    {
        #pragma omp critical
        cout << "Hello from main thread" << endl;
    }
        cout << "Jijijji\n";
}