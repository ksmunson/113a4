#include <atomic>

// this should be the same as RDekkers with the change that every
// relaxed access should be memory_order_relaxed.
// your job is to use the following MACRO to fix the mutex.
// Think about the reorderings allowed under TSO and where the fence
// needs to be placed.

#define FENCE asm volatile("mfence":::"memory");
using namespace std;

class dekkers_mutex {
public:
  dekkers_mutex() {
	flag =  (std::atomic_bool*) malloc((2) *sizeof(std::atomic_bool*));
	flag[0].store(false, memory_order_relaxed);
	flag[1].store(false, memory_order_relaxed);
	turn.store(0, memory_order_relaxed);
  }

  void lock(int tid) {
	if (tid == 0){
	   flag[0].store(true, memory_order_relaxed);
	   while (flag[1].load(memory_order_relaxed)) {
		  if (turn.load(memory_order_relaxed) != 0) {
			 flag[0].store(false, memory_order_relaxed);
			 while (turn.load(memory_order_relaxed) != 0) {
			   // busy wait
			 }
			 flag[0].store(true, memory_order_relaxed);
		  }
	   }
	} 
	else {
	   flag[1].store(true, memory_order_relaxed);
	   while (flag[0].load(memory_order_relaxed)) {
		  if (turn.load(memory_order_relaxed) != 1) {
			 flag[1].store(false, memory_order_relaxed);
			 while (turn.load(memory_order_relaxed) != 1) {
			   // busy wait
			 }
			 flag[1].store(true, memory_order_relaxed);
		  }
	   }
	}
  }

  void unlock(int tid) {
	if (tid == 0){
		FENCE;
		turn.store(1, memory_order_relaxed);
		flag[0].store(false, memory_order_relaxed);
	} else {
		FENCE;
	    turn.store(0, memory_order_relaxed);
		flag[1].store(false, memory_order_relaxed);
	}
  }

private:
  std::atomic_bool *flag;
  std::atomic_int turn;
};
