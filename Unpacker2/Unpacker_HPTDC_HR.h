#ifndef Unpacker_HPTDC_HR_h
#define Unpacker_HPTDC_HR_h

#include "UnpackingModule.h"

class Unpacker_HPTDC_HR : public UnpackingModule {
  
private:  
  UInt_t** leadTimes;
  UInt_t** trailTimes;
  UInt_t* leadMult;
  UInt_t* trailMult;
  
  int channelNumber;
  
  bool* firstLeadCorrect;
  
public:
  
  Unpacker_HPTDC_HR() { }
  Unpacker_HPTDC_HR(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_HPTDC_HR();
  
  void ProcessEvent(UInt_t* data);
  
  void SayHi() { cerr<<"HTPDC_HR: Hi from HPTDC_HR"<<endl; }
  
  UInt_t GetLeadTime(int channel, int mult) { return leadTimes[channel][mult]; }
  UInt_t GetLeadMult(int channel) { return leadMult[channel]; }
  UInt_t GetTrailTime(int channel, int mult) { return trailTimes[channel][mult]; }
  UInt_t GetTrailMult(int channel) { return trailMult[channel]; }
  bool GetFirstLeadCorrect(int channel) { return firstLeadCorrect[channel]; }
  
  void Clear();
  
  ClassDef(Unpacker_HPTDC_HR, 1);
  
};

#endif