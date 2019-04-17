class Receiver {
public:
 //constructor:
 Receiver ();
 //Receives a block of doubles such that the data
//is stored in index id of dataBlocks[][]
void receiveDataBlock(int id, double data[]);
 // print out all thread data one by one
void printBlocks();
}
private:
	double dataBlocks[MAX_NUM_OF_THREADS][DATA_BLOCK_SIZE];

}; //end class Receiver