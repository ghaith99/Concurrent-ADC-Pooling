class AdcInputChannel {
public:

	AdcInputChannel(int d);

  //used to request a sample from the sample channel:
	double getCurrentSample();
private:
	int currentSample;
}; //end class AdcInputChannel