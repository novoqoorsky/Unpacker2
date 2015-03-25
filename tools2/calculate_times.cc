#include "../Unpacker2/Event.h"
#include "../Unpacker2/TDCHit.h"
#include "../Unpacker2/TDCHitExtended.h"
#include "../Unpacker2/Unpacker2.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>


#define CHANNELS_NUMBER 32

int calculate_times(int eventsNum, const char* fileName)
{
  TChain chain("T");
  chain.Add(fileName);
    
  Event* pEvent = 0;
  TDCHit* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("event", &pEvent);

	string newFileName(fileName);
	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_times.root";

	TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
	TTree* new_tree = new TTree("T", "Normalized times tree");
	Event* new_event = 0;
	Int_t split = 2;
	Int_t bsize = 64000;
	new_tree->Branch("event", "Event", &new_event, bsize, split);
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;

  for(Int_t i = 0; i < entries; i++)
	{
    if (i % 10000 == 0) cout<<i<<endl;
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCHitsArray();
    if (pArray == 0) continue;
    TIter iter(pArray);

		int refTimeEpoch = 0;
		int refTimeCoarse = 0;
		int refTimeFine = 0;

    while( pHit = (TDCHit*) iter.Next() )
		{
			
			if ( (pHit->GetLeadsNum() > 0 && pHit->GetTrailsNum() > 0) || pHit->GetChannel() == 0 )
			{
				TDCHitExtended* new_hit = new_event->AddTDCHitExtended(pHit->GetChannel());
				int localTrailIndex = 0;
				double lastTime = -1;
				int localIndex = 0;

				if (pHit->GetChannel() == 0)
				{
					refTimeEpoch = pHit->GetLeadEpoch(0);
					refTimeCoarse = pHit->GetLeadCoarse(0);
					refTimeFine = pHit->GetLeadFine(0);
				}
	
				for (int j = 0; j < pHit->GetLeadsNum(); j++) 
				{
					double leadTime = (double) (
						(						
							( (((unsigned)pHit->GetLeadEpoch(j)) << 11) * 5.0) -
							( (((unsigned)refTimeEpoch) << 11) * 5.0 )
						)
					);
					leadTime += ((((pHit->GetLeadCoarse(j) - refTimeCoarse) * 5000.) - (pHit->GetLeadFine(j) - refTimeFine)) / 1000.);
					//cerr<<"Adding RISE on channel "<<pHit->GetChannel()<<" with epoch "<<pHit->GetLeadEpoch(j)<<" coarse "<<pHit->GetLeadCoarse(j)<<" fine "<<pHit->GetLeadFine(j);
					//printf(" absolute %f\n", leadTime);
					for(int l = 0; l <= localIndex; l++)
					{
						if (leadTime < new_hit->GetAbsoluteTimeLine(l) ) { // || new_hit->GetAbsoluteTimeLine(l) == -100000) {
							new_hit->ShiftEverythingUpByOne(l - 1);
	//						new_hit->SetShortTimeLine(leadTime, l);	
							new_hit->SetAbsoluteTimeLine(leadTime, l);
							new_hit->SetRisingEdge(true, l);
							localIndex++;
							new_hit->SetTimeLineSize(localIndex);
							break;
						}
					}
				}
				for (int k = 0; k < pHit->GetTrailsNum(); k++)
				{
					double trailTime = (double) (
						(						
							( (((unsigned)pHit->GetTrailEpoch(k)) << 11) * 5.0) -
							( (((unsigned)refTimeEpoch) << 11) * 5.0 )
						)
					);
					trailTime += ( (((pHit->GetTrailCoarse(k) - refTimeCoarse) * 5000.) - (pHit->GetTrailFine(k) - refTimeFine)) / 1000.);
					//cerr<<"Adding FALL on channel "<<pHit->GetChannel()<<" with epoch "<<pHit->GetTrailEpoch(k)<<" coarse "<<pHit->GetTrailCoarse(k)<<" fine "<<pHit->GetTrailFine(k);
					//printf(" absolute %f\n", trailTime);
					for(int l = 0; l <= localIndex; l++)
					{
						if (trailTime < new_hit->GetAbsoluteTimeLine(l) ) { // || new_hit->GetAbsoluteTimeLine(l) == -100000) {
							new_hit->ShiftEverythingUpByOne(l - 1);
//							new_hit->SetShortTimeLine(trailTime, l);
							new_hit->SetAbsoluteTimeLine(trailTime, l);
							new_hit->SetRisingEdge(false, l);
							localIndex++;
							new_hit->SetTimeLineSize(localIndex);
							break;
						}
					}
				}
				new_hit->SetTimeLineSize(localIndex);
//				new_hit->PrintOut();
			}
		}

		new_tree->Fill();
		new_event->Clear();
	}

	new_tree->Write();

	new_file->Close();

	return 0;
}
