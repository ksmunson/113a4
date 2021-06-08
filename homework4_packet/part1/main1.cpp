#include "common.h"
#include <iostream>
#include <thread>
#include <chrono>

//blur func
void blur(double *input, double *output, int num_threads, int tid) {
    int chunk_size = SIZE / num_threads; 
    int start = chunk_size * tid ;
	if (tid == 0){
		start++;
	}
    int end = start + chunk_size ;
	if (tid == num_threads-1){
		end = end -1;
	}
	for (int i = start; i < end; i++){
		output[i] = (input[i] + input[i+1] + input [i-1]) / 3;
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
  /*for (int j = 0; j< SIZE; j++){
  std::cout << "input: " << input[j] << std::endl;
   std::cout << "output: " << output[j] << std::endl;
  }*/
  auto time_start = std::chrono::high_resolution_clock::now();
  for (int r = 0; r < REPEATS; r++) {
    // Launch threads to compute the blur
	std::thread thread_arr[num_threads];
	for (int i = 0; i < num_threads; i++){
       thread_arr[i] = std::thread(blur, input, output, num_threads, i);
    }
   // Join threads
    for (int i = 0; i < num_threads; i++) {
        thread_arr[i].join();
    } 
	// given solution
	for (int i = 1; i < SIZE - 1; i++) {
		output[i] = (input[i] + input[i+1] + input[i-1])/3;
	}
    // Swap input and output pointers.
	double *tmp = input;
	input = output;
	output = tmp;
  }
  
  for (int j = 0; j< SIZE; j++){
  //std::cout << "input: " << input[j] << std::endl;
   //std::cout << "output: " << output[j] << std::endl;
  }

  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
  double time_seconds = time_duration.count()/1000000000.0;
  std::cout << "timings: " << time_seconds << std::endl;
      
}
