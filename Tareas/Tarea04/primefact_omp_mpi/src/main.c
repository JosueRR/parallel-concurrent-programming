/*
*   Copyright 2021 Josue Retana  - UCR
*   
*   Main del proyecto
*/

#include "interface.h"
#include "mpi_control.h"

int main(int argc, char * args[]) {
  // interface_run();
  int error = mpi_control_handle(argc, args);
  // we return a 1 if there was any error in the factoring process
  return error;
}
