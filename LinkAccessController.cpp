class LinkAccessController {
public:
 LinkAccessController(Receiver& r) : myReceiver(r), numOfAvailableLinks(NUM_OF_LINKS)
 {
 	for (int i = 0; i < NUM_OF_LINKS; i++) {
 		commsLinks.push_back(Link(myReceiver, i));
 	}
 }
 //Request a comm's link: returns an available Link.
 //If none are available, the calling thread is suspended.
 Link requestLink() {

 	//Suspend/wait for link to be available
 	while(numOfAvailableLinks <= 0);

 	int linkNum;
 	for(linkNum = 0;linkNum  < NUM_OF_LINKS-1; linkNum++){
 		if(!commsLinks[linkNum].isInUse())
			break; //found unused link, go out of the loop
	}
	commsLinks[linkNum].setInUse();
	numOfAvailableLinks--;

 	return commsLinks[linkNum]; //return unused link
 }

 //Release a comms link:
 void releaseLink(Link& releasedLink) {
 	releasedLink.setIdle();
 	numOfAvailableLinks++;
 }

private:
 Receiver& myReceiver; //Receiver reference
 int numOfAvailableLinks;
 std::vector<Link> commsLinks;
 std::mutex LAC_mu; //mutex
}; //end class LinkAccessController

