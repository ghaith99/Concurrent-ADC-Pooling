class ADC {
public:
    //constructor: initialises a vector of ADCInputChannels
    //passed in by reference:
	ADC(std::vector < AdcInputChannel > & channels);

	void requestADC(int c);
	double sampleADC() ;
	void releaseADC();

private:
	Lock theADCLock;
	int sampleChannel;
  	std::vector < AdcInputChannel > & adcChannels; //vector reference
  	std::mutex ADC_mu; //mutex
}; //end class ADC
