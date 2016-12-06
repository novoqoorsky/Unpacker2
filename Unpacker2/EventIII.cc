#include <iostream>
#include "EventIII.h"

using namespace std;

ClassImp(EventIII);

EventIII::EventIII() : TNamed("EventIII", "EventIII") {   
  TDCChannels = new TClonesArray("TDCChannel", 2100);
  
  TDCChannels->Clear();
  
  totalNTDCChannels = 0;
}

TDCChannel* EventIII::AddTDCChannel(int channel) {
  TClonesArray& thits = *TDCChannels;
  TDCChannel* ch = new (thits[totalNTDCChannels++]) TDCChannel();
  ch->SetChannel(channel);
  return ch;
}


void EventIII::Clear(void) {  
  TDCChannels->Clear();
  totalNTDCChannels = 0;
}
