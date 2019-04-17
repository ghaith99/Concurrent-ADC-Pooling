class Link {
public:
 Link (Receiver& r, int linkNum); //Constructor


 //check if the link is currently in use
 bool isInUse();
 //set the link status to busy
 void setInUse();
 //set the link status to idle
 void setIdle();
 //write data[] to the receiver
 //id is the thread id
 void writeToDataLink(int id, double data[]);
 //returns the link Id
 int getLinkId();
private:
	bool inUse;
 	Receiver& myReceiver; //Receiver reference
 	int linkId;
}; //end class Link