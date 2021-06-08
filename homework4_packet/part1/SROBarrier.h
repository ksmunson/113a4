#include <atomic>
#include <thread>

class barrier_object {
 public:
  barrier_object() {
    // Probably don't need to do anything here.
  }

  void init(int num_threads) {
	count = num_threads;
	size = num_threads;
	sense = false;
	threadSense =  (std::atomic_bool*) malloc((num_threads + 1) *sizeof(std::atomic_bool));
	for (int j = 0; j < num_threads; j++){
		threadSense[j] = !(sense.load());
	}
  }

  void barrier(int tid) {
    // Implement me
	//yield in spin loop
	//relaxed peaking on loads see hw2 I think
	bool mySense = threadSense[tid].load(std::memory_order_relaxed);
	int position = atomic_fetch_sub(&count, 1);
	if (position == 1) {
		count = size;
		sense = mySense;
		//std::cout << "ok to go ahead" << tid << std::endl;
	} else {
		while (sense.load(std::memory_order_relaxed) != mySense) {
			std::this_thread::yield();
		}
	}
	threadSense[tid] = !mySense;
  }

private:
  // Give me some private variables
  std::atomic_int count;
  int size;
  std::atomic_bool sense;
  std::atomic_bool *threadSense;
};
