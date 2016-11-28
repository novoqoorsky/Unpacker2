#include "TDCChannel.h"

using namespace std;

ClassImp(TDCChannel);

TDCChannel::TDCChannel() {
	hitsNum = 0;
	channel = -1;
}

TDCChannel::~TDCChannel() {}


void TDCChannel::AddHit(double lead, double trail) {
	  leadTimes.push_back(lead);
	  trailTimes.push_back(trail);
	  
	  hitsNum++;
}
