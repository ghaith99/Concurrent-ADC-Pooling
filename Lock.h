class Lock {
public:
	Lock();
    //returns a flag to indicate when a thread should be blocked
	void setLock();

    bool getLock();

    void unlock();
    
private:
	std::mutex Lock_mu;
	bool open;
}; //end class Lock
