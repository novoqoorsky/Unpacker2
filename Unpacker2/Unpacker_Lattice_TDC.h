#ifndef Unpacker_Lattice_TDC_h
#define Unpacker_Lattice_TDC_h

#include "UnpackingModule.h"

class Unpacker_Lattice_TDC : public UnpackingModule {
  
private:  
  UInt_t** leadTimes;
  UInt_t** trailTimes;
  UInt_t* leadMult;
  UInt_t* trailMult;
  
  int channelNumber;
  
public:
  
  Unpacker_Lattice_TDC() { }
  Unpacker_Lattice_TDC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_Lattice_TDC();
  
  void ProcessEvent(UInt_t* data);
  
  void SayHi() { cerr<<"HTPDC_HR: Hi from HPTDC_HR"<<endl; }
  
  UInt_t GetLeadTime(int channel, int mult) { return leadTimes[channel][mult]; }
  UInt_t GetLeadMult(int channel) { return leadMult[channel]; }
  UInt_t GetTrailTime(int channel, int mult) { return trailTimes[channel][mult]; }
  UInt_t GetTrailMult(int channel) { return trailMult[channel]; }
  
  void Clear();
  
  ClassDef(Unpacker_Lattice_TDC, 1);
  
};

#endif