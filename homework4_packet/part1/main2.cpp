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

void repeated_blur(double *input, double *output, int num_threads, int tid){
	//address this in a bit i guess
	for (int r = 0; r < REPEATS; r++) {
		int chunk_size = SIZE / num_threads; 
		int start = chunk_size * tid ;
		if (tid == 0){
			start++;
		}
		int end = start + chunk_size ;
		if (tid == num_threads-1){
			end = end -1;
		}
		
		for (int i = start; i < end; i++) {
			output[i] = (input[i] + input[i+1] + input[i-1])/3;
		}
		double *tmp = input;
		input = output;
		output = tmp;
		
		B.barrier(tid);
	}
}

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
	std::thread thread_arr[num_threads];
	for (int i = 0; i < num_threads; i++){
       thread_arr[i] = std::thread(repeated_blur, input, output, num_threads, i); //check the function used
    }
  // Join threads once
    for (int i = 0; i < num_threads; i++) {
        thread_arr[i].join();
    } 
	//verify correct
	for (int j = 0; j< SIZE; j++){
		//std::cout << "input: " << input[j] << std::endl;
		//std::cout << "output: " << output[j] << std::endl;
    }
  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;

  std::cout << "timings: " << time_seconds << std::endl;
      
}
