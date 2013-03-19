#ifndef UnpackingModule_h
#define UnpackingModule_h

#include <TObject.h>
#include <iostream>
#include <string>
#include <map>
#include "Event.h"

using namespace std;

class UnpackingModule : public TObject {

private:
  string boardType;
  string boardAddress;
  string hubAddress;
  int channelNumber;
  int channelOffset;
  int resolution;
  string measurementType;
  
  bool invertBytes;
  
  map<std::string, UnpackingModule*> internalUnpackers;
 
public:
  
  UnpackingModule() {}
  UnpackingModule(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~UnpackingModule() {}
  
  void AddUnpacker(std::string s, UnpackingModule* u) { internalUnpackers[s] = u; }
  UnpackingModule* GetUnpacker(std::string s) { return internalUnpackers[s]; }
  
  void SetBoardType(string t) { boardType = t; }
  void SetBoardAddress(string t) { boardAddress = t; }
  void SetHubAddress(string t) { hubAddress = t; }
  void SetChannelNumber(int t) { channelNumber = t; }
  void SetResolution(int t) { resolution = t; }
  void SetMeasurementType(string t) { measurementType = t; }
  void SetInvertBytes(bool dec) { invertBytes = dec; }
  
  string GetBoardType() { return boardType; }
  string GetBoardAddress() { return boardAddress; }
  string GetHubAddress() { return hubAddress; }
  int GetChannelNumber() { return channelNumber; }
  int GetChannelOffset() { return channelOffset; }
  int GetResolution() { return resolution; }
  string GetMeasurementType() { return measurementType; }
  bool GetInvertBytes() { return invertBytes; }
  
  virtual void ProcessEvent(UInt_t* data);
  virtual void ProcessEvent(UInt_t* data, Event* evt);
  
  virtual void GetADCHits();
  virtual void GetTDCHits();
  
  virtual void SayHi();
  
  virtual void Clear();
 
  string UIntToString(UInt_t t) { char buf[4]; sprintf(buf, "%04X", t); return string(buf); }
  
  map<std::string, UnpackingModule*>::iterator GetInternalUnpackersIterBegin() { return internalUnpackers.begin(); }
  map<std::string, UnpackingModule*>::iterator GetInternalUnpackersIterEnd() { return internalUnpackers.end(); }
  
  // part of TDC unpacking interface
  virtual UInt_t GetLeadTime(int channel, int mult) { return -1; }
  virtual UInt_t GetLeadMult(int channel) { return -1; }
  virtual UInt_t GetTrailTime(int channel, int mult) { return -1; }
  virtual UInt_t GetTrailMult(int channel) { return -1; }
  virtual void SetReferenceChannel(int t) {}
  virtual bool GetFirstLeadCorrect(int channel) { return false; }
  
  // part of ADC unpacking interface
  virtual Int_t GetSample(Int_t channel, Int_t sampleNr) {return -1; }
  virtual Int_t GetDspSum(Int_t channel) {return -1; }
  virtual Int_t GetDspMean(Int_t channel) {return -1; }
  virtual Int_t GetDspCfA(Int_t channel) {return -1; }
  virtual Int_t GetDspCfB(Int_t channel) {return -1; }
  virtual Int_t GetDspCfT(Int_t channel) {return -1; }
  virtual Int_t GetNumberOfSamples() {return -1; }
 
  UInt_t ReverseHex(UInt_t n);
  
  bool debugMode;
  
  ClassDef(UnpackingModule,1);
  
};


#endif