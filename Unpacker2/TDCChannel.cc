#include "TDCChannel.h"

using namespace std;

ClassImp(TDCChannel);

TDCChannel::TDCChannel() {
	hitsNum = 0;
	channel = -1;
}

TDCChannel::~TDCChannel() {}


void TDCChannel::AddHit(double lead, double trail) {
	if (hitsNum < MAX_FULL_HITS - 1) {
	  
	  leadTimes.push_back(lead);
	  trailTimes.push_back(trail);
	  
	  hitsNum++;

	}
}
