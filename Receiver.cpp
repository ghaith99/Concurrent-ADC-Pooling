#include "Receiver.h"

class Receiver {
public:
 //constructor:
 Receiver () { //syntax -no initialiser list, no ":"
 //initialise dataBlocks:
 for (int i = 0; i < MAX_NUM_OF_THREADS; i++) {
 	for (int j = 0; j < DATA_BLOCK_SIZE; j++) {
 		dataBlocks[i][j] = 0;
 	}
 }
}
 //Receives a block of doubles such that the data
//is stored in index id of dataBlocks[][]
void receiveDataBlock(int id, double data[]) {
	for(int i =0; i < DATA_BLOCK_SIZE; i++){
		dataBlocks[id][i] = data[i];
	}
}
 // print out all thread data one by one
void printBlocks() {
	for (int i = 0; i < MAX_NUM_OF_THREADS; i++) {
		for (int j = 0; j < DATA_BLOCK_SIZE; j++) {
 		cout << dataBlocks[i][j];
		}
		cout << endl;
	}
}
private:
	double dataBlocks[MAX_NUM_OF_THREADS][DATA_BLOCK_SIZE];

}; //end class Receiver