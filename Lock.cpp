#include "Lock.h"
class Lock {
public:
	Lock() {
		open = true;
	}
    //returns a flag to indicate when a thread should be blocked
	void setLock() {
    	if(open) { //ADC is Available
    		open = false;
    	}
    }

    bool getLock(){
    	std::unique_lock<mutex> locker(Lock_mu); //Lock Print out
    	return open;
    	locker.unlock();
    }

    void unlock() {
    	open = true;
    }
private:
	std::mutex Lock_mu;
	bool open;
}; //end class Lock
