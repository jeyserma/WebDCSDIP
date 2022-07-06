#include "../interface/dip.hpp"

class GeneralDataListener:public DipSubscriptionListener {
	
    public:

	void handleMessage(DipSubscription *sub, DipData &message) {
			string tn = (string)sub->getTopicName();
            for(uint i=0; i<d->size(); i++) {
				if(tn == d->at(i).subscription) {
                    if(d->at(i).type == "float") d->at(i).value = to_string(message.extractFloat(d->at(i).identifier.c_str()));
                    if(d->at(i).type == "int") d->at(i).value = to_string(message.extractInt(d->at(i).identifier.c_str()));
                    if(d->at(i).type == "bool") d->at(i).value = to_string(message.extractBool(d->at(i).identifier.c_str()));
			        if(d->at(i).type == "string") d->at(i).value = message.extractString(d->at(i).identifier.c_str());
                }
            }
	}
	
	void connected(DipSubscription *arg0) {
		//printf("\nPublication source %s available\n", arg0->getTopicName());
	}

	void disconnected(DipSubscription *arg0, char *arg1) {
		printf("\nPublication source %s unavailable\n", arg0->getTopicName());
	}

	void handleException(DipSubscription* subscription, DipException& ex){
		printf("Subs %s has error %s\n", subscription->getTopicName(), ex.what());
	}
};



int main(const int argc, const char ** argv) {
    
    // Setup DIP classes
    GeneralDataListener *handler;
    handler = new GeneralDataListener();
    DipFactory *dip;
    dip = Dip::create("");
	dip->setDNSNode("dipnsgpn1,dipnsgpn2");
    vector<DipSubscription*> DipSubscriptions;
	
	
	// assign DIP
	DIPParameter param1; 
	param1.subscription = "dip/GIFpp/Atmospheric_Pressure";
	param1.identifier = "__DIP_DEFAULT__";
	param1.type = "float";
    d->push_back(param1);
	
	
	DIPParameter param2; 
	param2.subscription = "dip/GIFpp/PAXN1647";
	param2.identifier = "Name";
	param2.type = "string";
    d->push_back(param2);
	
	DIPParameter param3; 
	param3.subscription = "dip/GIFpp/EnvSensors/201/ZONE2";
	param3.identifier = "T";
	param3.type = "float";
    d->push_back(param3);
	
	DIPParameter param4; 
	param4.subscription = "dip/GIFpp/EnvSensors/201/ZONE2";
	param4.identifier = "P";
	param4.type = "float";
    d->push_back(param4);
	
	DIPParameter param5; 
	param5.subscription = "dip/GIFpp/Irradiator/SourceOFF";
	param5.identifier = "__DIP_DEFAULT__";
	param5.type = "bool";
    d->push_back(param5);
	

	
	// update the subscriptions, get the data and wait a second to update the subscriptions
	for(uint i=0; i<d->size(); i++) {
        DipSubscriptions.push_back(dip->createDipSubscription(d->at(i).subscription.c_str(), handler));
        DipSubscriptions.at(i)->requestUpdate();
    }
	sleep(1);
	
	
	// display the data
	for(uint i=0; i<d->size(); i++) {
		cout << d->at(i).subscription << " " << d->at(i).identifier << " " << d->at(i).value << endl;
	}

    
    // close connections
    for(uint i=0; i<DipSubscriptions.size(); i++) dip->destroyDipSubscription(DipSubscriptions.at(i));
    delete handler;
    delete dip;
    

    return 0;
}
