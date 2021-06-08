#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

#include "SRBarrier.h"
barrier_object B;

#define TEST_ITERATIONS (1024*256) //1024*256
int var0 = 0;
int var1 = 0;
atomic_int x(0);
atomic_int y(0);
void t0_function() {
  // complete me!
  	B.barrier(0);
    x.store(1);
  var0 = y.load();
}

void t1_function() {
  // complete me!
  	B.barrier(1);
    y.store(1);
  var1 = x.load();
}


int main() {

  int output0 = 0;
  int output1 = 0;
  int output2 = 0;
  int output3 = 0;
  B.init(2);

  for (int i = 0; i < TEST_ITERATIONS; i++) {
    // Run a test iteration
	var0 = 0;
	var1 = 0;
	x = 0;
	y = 0;
	
    std::thread t1 = std::thread(t0_function);
	std::thread t2 = std::thread(t1_function);
	t1.join();
	t2.join();
    // Record a histogram, fill in the conditions
    
    if (var0 == 1, var1== 1) {
      output0++;
    }
    else if (var0 == 1, var1 == 0) {
      output1++;
    }
    else if (var0 == 0, var1== 1) {
      output2++;
    }

    // This should be the relaxed behavior
    else if (var0 == 0 , var1 == 0) {
      output3++;
    }
	
	
  }

  // Complete the print out using your output instantiations
  cout << "histogram of different observations:" << endl;
  cout << "output0: var0 = 1, var1 = 1 " << output0 << endl;
  cout << "output1: var0 = 1, var1 = 0 " << output1 << endl;
  cout << "output2: var0 = 0, var1 = 1 " << output2 << endl;
  cout << "output3: var0 = 0, var1 = 0 " << output3 << endl << endl;
  cout << "relaxed behavior frequency: " << float(output3)/float(TEST_ITERATIONS) << endl;
  
  return 0;
  
}
