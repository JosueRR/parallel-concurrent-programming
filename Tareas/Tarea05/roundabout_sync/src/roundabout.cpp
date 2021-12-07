/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Proyecto rotonda sincronizada
*/

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>
#include <vector>



int main(int argc, char* argv[]) {
    // Analyze arguments
    shared_data_t shared_data;
    shared_data.drive_min_delay = 0;
    shared_data.drive_max_delay = 0;
    shared_data.verbose = false;
    if (argc >= 3) {
        shared_data.drive_min_delay = atoi(argv[1]);
        shared_data.drive_max_delay = atoi(argv[2]);
    }
    if (argc >= 4) {
        if (strcmp(argv[3], "-v") == 0) {
            shared_data.verbose = true;
        }
    }
    return 0;
}

