#include "AdcInputChannel.h"

class AdcInputChannel {
public:

	AdcInputChannel(int d): currentSample(d) {
	}

  //used to request a sample from the sample channel:
	double getCurrentSample() {
		return currentSample;
	}
private:
	int currentSample;
}; //end class AdcInputChannel