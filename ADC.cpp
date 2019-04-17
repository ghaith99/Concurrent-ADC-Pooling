#include "ADC.h"


class ADC {
public:
    //constructor: initialises a vector of ADCInputChannels
    //passed in by reference:
	ADC(std::vector < AdcInputChannel > & channels): adcChannels(channels) {
	}

	void requestADC(int c) {

		//Check lock status
		if(!theADCLock.getLock()){

			std::unique_lock<mutex> locker(ADC_mu); //Lock Print out

			cout << "ADC is locked, thread "<< search(std::this_thread::get_id()) << " is about to suspend.. " << endl;

			locker.unlock(); //Unlock Print out

			 //block/suspend the thread until lock is true
			while(!theADCLock.getLock());
		}

		sampleChannel = c;

		//Lock the ADC

		theADCLock.setLock();
		//print thread identity when the call is successful
		std::unique_lock<mutex> locker(ADC_mu); //Lock Print out
		cout << "ADC Locked by thread " << search(std::this_thread::get_id()) << endl;
		locker.unlock(); //Unlock Print out
	}

	double sampleADC() {

		std::unique_lock<mutex> locker(ADC_mu); //Lock Print out
		cout << "sample value from thread " << search(std::this_thread::get_id()) << " = " << sampleChannel*2 << endl;

		locker.unlock(); //Unlock Print out

		return sampleChannel*2;
	}
	void releaseADC() {
		theADCLock.unlock();
		// printing out thread identity once more
		std::unique_lock<mutex> locker(ADC_mu); //Lock Print out
		cout << "ADC unlocked by thread " << search(std::this_thread::get_id()) << endl;
		locker.unlock(); //Unlock Print out
	}

private:
	Lock theADCLock;
	int sampleChannel;
  	std::vector < AdcInputChannel > & adcChannels; //vector reference
  	std::mutex ADC_mu; //mutex
}; //end class ADC
