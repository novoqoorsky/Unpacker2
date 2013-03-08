#ifndef TDCHit_h
#define TDCHit_h

#include <TObject.h>

#define MAX_HITS 100

class TDCHit : public TObject {
  
private:
  Int_t channel;
  Int_t leadTime1;
  Int_t trailTime1;
  Int_t leadTimes[MAX_HITS];
  Int_t trailTimes[MAX_HITS];
  Int_t leadsNum;
  Int_t trailsNum;
  
public:

  TDCHit();
  ~TDCHit();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  
  void AddLeadTime(Int_t time);
  void AddTrailTime(Int_t time);
  
  Int_t GetChannel() { return channel; }
  Int_t GetLeadTime1() { return leadTime1; }
  Int_t GetTrailTime1() { return trailTime1; }
  Int_t GetLeadsNum() { return leadsNum; }
  Int_t GetTrailsNum() { return trailsNum; }
  Int_t GetLeadTime(int mult) { return leadTimes[mult]; }
  Int_t GetTrailTime(int mult) { return trailTimes[mult]; }
  
  ClassDef(TDCHit,1);
};

#endif