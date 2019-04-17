//pre-processor directives:
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <random>
#include <thread>
#include <vector>
#include <time.h>


using namespace std;
//global constants:
int const MAX_NUM_OF_CHAN = 6; //number of AdcInputChannels
int const MAX_NUM_OF_THREADS = 6;
int const DATA_BLOCK_SIZE = 20;
int const NUM_OF_LINKS = 3;

//global variables:

std::mutex mutex_ThreadIds; //declare a mutex

std::map <std::thread::id, int> threadIDs;

//function prototypes: (if used)
int search(std::thread::id thID);


int search(std::thread::id thID){
	std::map <std::thread::id, int>::iterator it = threadIDs.find(thID);

 	if (it == threadIDs.end()) return -1; //thread 'id' NOT found

 	else return it->second; //thread 'id' found, return the associated integer –note the syntax.
 }

//run function –executed by each thread:
 void run(ADC & theADC, int id, LinkAccessController & lac) {

	//associate the thread 'id' with an integer value in a map
	std::unique_lock<std::mutex> map_locker(mutex_ThreadIds); //lock the map via the mutex.
	//insert the threadID and id into the map:
	threadIDs.insert(std::make_pair(std::this_thread::get_id(), id));
	mutex_ThreadIds.unlock(); //we're done, unlock the map.

  	//to store the sampled data: (for part A2 only)
	double sampleBlock[DATA_BLOCK_SIZE] = {0.0};  //initialise all elements to 0

	//read 40 ADC Values and store in SampleBlock to be transmitted(by the reciever)
	for (int i = 0; i<DATA_BLOCK_SIZE ;i++) {

	    // request use of the ADC; channel to sample is id:
		theADC.requestADC(id);

	    // sample the ADC:
		sampleBlock[i] = theADC.sampleADC();
		theADC.releaseADC();

	    // delay for random period between 0.1s - .5s:
		std::random_device rd; //used to obtain a seed for the random number engine
		std::mt19937 gen(time(NULL)); //Standard 'mersenne_twister_engine' seeded with rd()
		std::uniform_int_distribution<> dis(100, 500); //generate a random integer
		//between .1 to .5
		int n = dis(gen);
		//cout << "DEBUG: Sleep : --------------->>>>>>>>>>>"<< std::chrono::milliseconds(n).count() << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(n));
	}

	Link link = lac.requestLink();
	//transmit the data (sampleBlock) to the Receiver.
	link.writeToDataLink(search(std::this_thread::get_id()), sampleBlock);
	//Release the link, printing out its identity once more.
	lac.releaseLink(link);

	cout << "Thread "<< search(std::this_thread::get_id()) << " Finished Sending" << endl;;
}

int main() {
  //initialise the ADC channels:
	std::vector < AdcInputChannel > adcChannels;
	for (int i = 0; i < MAX_NUM_OF_CHAN; i++) {
	//each AdcInputChannel is initialised with a different value
		adcChannels.push_back(AdcInputChannel(i));
	}

  // Instantiate the ADC:
	ADC adc(adcChannels);

	// Instantiate the Receiver:
	Receiver receiver;

 	// Instantiate the LinkAccessController
	LinkAccessController lac(receiver);

  //instantiate and start the threads:
  std::thread the_threads[MAX_NUM_OF_THREADS]; //array of threads

  for(int i=0;i<MAX_NUM_OF_THREADS;i++)
  	the_threads[i]=std::thread(run,std::ref(adc),i, std::ref(lac));

  //wait for the threads to finish:
  for (int i = 0; i < MAX_NUM_OF_THREADS; i++) {
  	the_threads[i].join();
  }

   // Print out the data in the Receiver:
  receiver.printBlocks();

  cout << "All threads terminated" << endl;
  return 0;
}
