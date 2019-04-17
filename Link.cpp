#include "Link.h"

class Link {
public:
 Link (Receiver& r, int linkNum) //Constructor
 : inUse(false), myReceiver(r), linkId(linkNum)
 {}


 //check if the link is currently in use
 bool isInUse() {
 	return inUse;
 }
 //set the link status to busy
 void setInUse() {
 	inUse = true;
 }
 //set the link status to idle
 void setIdle() {
 	inUse = false;
 }
 //write data[] to the receiver
 //id is the thread id
 void writeToDataLink(int id, double data[]) {
 	myReceiver.receiveDataBlock(id, data);
 }
 //returns the link Id
 int getLinkId() {
 	return linkId;
 }
private:
	bool inUse;
 	Receiver& myReceiver; //Receiver reference
 	int linkId;
}; //end class Link