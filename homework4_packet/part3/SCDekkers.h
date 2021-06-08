#include <atomic>

class dekkers_mutex {
public:
  dekkers_mutex() {
    // implement me!
	flag =  (std::atomic_bool*) malloc((2) *sizeof(std::atomic_bool*));
	flag[0].store(false);
	flag[1].store(false);
	turn.store(0);
  }

  void lock(int tid) {
    // implement me!
	if (tid == 0){
	   flag[0].store(true);
	   while (flag[1].load()) {
		  if (turn.load() != 0) {
			 flag[0].store(false);
			 while (turn.load() != 0) {
			   // busy wait
			 }
			 flag[0].store(true);
		  }
	   }
	} else {
	   flag[1].store(true);
	   while (flag[0].load()) {
		  if (turn.load() != 1) {
			 flag[1].store(false);
			 while (turn.load() != 1) {
			   // busy wait
			 }
			 flag[1].store(true);
		  }
	   }
	}
  }

  void unlock(int tid) {
    // implement me!
	if (tid == 0){
		turn.store(1);
		flag[0].store(false);
	} else {
	    turn.store(0);
		flag[1].store(false);
	}
	//pass turn 
	//reset flag
  }

private:
  // Give me some private variables  
  std::atomic_bool *flag;
  std::atomic_int turn;
};
