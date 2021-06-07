#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>

#if defined(SRBARRIER)
#include "SRBarrier.h"
#elif defined(SROBARRIER)
#include "SROBarrier.h"
#else
#error "no barrier specified!"
#endif
barrier_object B;


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
 
  B.init(num_threads);
  auto time_start = std::chrono::high_resolution_clock::now();

  // Launch threads once
  // Join threads once
  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;

  std::cout << "timings: " << time_seconds << std::endl;
      
}
