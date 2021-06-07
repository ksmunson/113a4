#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {
  int num_threads = 8;
  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }

  double *input = new double[SIZE];
  double *output = new double[SIZE];


  for (int i = 0; i < SIZE; i++) {
    double randval = fRand(-100.0, 100.0);
    input[i] = randval;
    output[i] = randval;    
  }

  auto time_start = std::chrono::high_resolution_clock::now();
  for (int r = 0; r < REPEATS; r++) {
    // Launch threads to compute the blur
    // Join threads
    // Swap input and output pointers.
  }

  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  std::cout << "timings: " << time_seconds << std::endl;
      
}
