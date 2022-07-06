#ifndef DIP_H
#define DIP_H

#include <string>
#include <stdio.h>
#include <vector>
#include <unistd.h>

#include "../DIPSoftware/include/Dip.h"
#include "../DIPSoftware/include/DipSubscription.h"

using namespace std;

struct DIPParameter {
    string subscription;
	string identifier;
    string type;
    string value;	
};

vector<DIPParameter> *d = new vector<DIPParameter>;


#endif
