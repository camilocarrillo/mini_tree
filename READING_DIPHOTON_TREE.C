#define READING_DIPHOTON_TREE_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "Riostream.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>

#include <iostream>
#include "Riostream.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <TEfficiency.h>

//#define Nhltpaths 442
//#define Maxselection 7


#include "READING_DIPHOTON_TREE.h"


void READING_DIPHOTON_TREE::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L READING_DIPHOTON_TREE.C
//      Root > READING_DIPHOTON_TREE t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   //Declaration 



   TFile * theFileOut;
   TH1F * ptLead[7  ];
   TH1F * ptTrail[7  ];
   TH1F * ptLeadNorm[7  ];
   TH1F * ptTrailNorm[7  ];
   TH1F * massDiphotonhisto[7  ];
   TH1F * massHiggshisto[7  ];
   TH1F * higgsEta[7  ];
   TH1F * higgsPhi[7  ];
   TH1F * higgsP[7  ];
   TH1F * higgsPt[7  ];
   TH2F * phi1phi2[7  ];
   TH2F * eta1eta2[7  ];
   TH2F * pt1pt2[7  ];
   TH2F * pt1pt2Norm[7  ];
   TH2F * wide_pt1pt2[7  ];
   const Double_t bins[19]={5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,90,100,110};
   bool fillhisto[7  ];
   //string arrayHLTpathsNames[442  ];
   bool filled_hlt_names;
   int selection;
   //beginJobs
   filled_hlt_names=false;
   theFileOut = new TFile("-fileout-", "RECREATE");
   TString name;
   for(selection=0;selection<7  ;selection++){ //Loop over the different histograms   
     name = Form("ptLead_%d",selection);      ptLead[selection]       = new TH1F (name,name,100,0.,120.);
     name = Form("ptTrail_%d",selection);     ptTrail[selection]      = new TH1F (name,name,100,0.,120.);
     name = Form("ptLeadNorm_%d",selection);  ptLeadNorm[selection]        = new TH1F (name,name,100,0.,1.);
     name = Form("ptTrailNorm_%d",selection); ptTrailNorm[selection]       = new TH1F (name,name,100,0.,1.);
     name = Form("massDiphoton_%d",selection);massDiphotonhisto[selection] = new TH1F (name,name,100,80.,180.);
     name = Form("massHiggs_%d",selection);   massHiggshisto[selection]    = new TH1F (name,name,100,80.,180.);
     name = Form("higgsEta_%d",selection);    higgsEta[selection]          = new TH1F (name,name,100,-5,5);
     name = Form("higgsPhi_%d",selection);    higgsPhi[selection]          = new TH1F (name,name,180,-3.15,3.15);
     name = Form("higgsP_%d",selection);      higgsP[selection]            = new TH1F (name,name,500,0,1200);
     name = Form("higgsPt_%d",selection);     higgsPt[selection]           = new TH1F (name,name,500,0,1200);
     name = Form("phi1phi2_%d",selection);    phi1phi2[selection]          = new TH2F (name,name,180,-3.15,3.15,180,-3.15,3.15);
     name = Form("eta1eta2_%d",selection);    eta1eta2[selection]          = new TH2F (name,name,100,-5,5,100,-5,5);
     name = Form("pt1pt2_%d",selection);      pt1pt2[selection]            = new TH2F (name,name,100,0.,110.,100,0.,110.);
     name = Form("pt1pt2Norm_%d",selection);  pt1pt2Norm[selection]        = new TH2F (name,name,100,0.,1.,100,0.,1.);
     name = Form("wide_pt1pt2_%d",selection); wide_pt1pt2[selection]       = new TH2F (name,name,19-1,bins,19-1,bins);
   }
   
   //loop

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   
     nbytes += nb;

     /*
     std::cout<<event_hlt_bit->at(1)<<" "<<event_hlt_bit->at(2)<<" "<<event_hlt_bit->at(3)<<" "<<Diphoton_Mass<<" "<<Diphoton_PT<<" "<<Diphoton_Eta<<" "<<Diphoton_Phi<<std::endl;
     
     std::cout<<"sizes: hlt_bit"<<event_hlt_bit->size()<<" names_hlt"<<event_hlt_path_names_HLT->size()<<std::endl;     
     
     
     if(filled_hlt_names==false){
       for(int k=0;k<event_hlt_path_names_HLT->size();k++){
	 std::cout<<"k="<<k<<" event_hlt_path_names_HLT->at(k)="<<event_hlt_path_names_HLT->at(k)<<std::endl;
       }
       filled_hlt_names=true;
     }
     
     if(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 194)!=event_hlt_bit->end()) std::cout<<"bit 194 was fired"<<std::endl;
     if(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 1)!=event_hlt_bit->end()) std::cout<<"bit 1 was fired"<<std::endl;
     */
     //std::cout<<"fillhisto1 ";
     for(selection=0;selection<7  ;selection++){
       fillhisto[selection]=false;
       //std::cout<<fillhisto[selection]<<" ";
     }
     //std::cout<<std::endl;

     bool bit194=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 194)!=event_hlt_bit->end());
     bool bit195=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 195)!=event_hlt_bit->end());
     bool bit205=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 205)!=event_hlt_bit->end());
     
     fillhisto[0]=true; //all minitree level just for reference.                                                                
     fillhisto[1]=//bool for Numerator
       //Transition Barrel Endcap Zone Excluded
       !((fabs(Diphoton_LeadEta)>1.4442&&fabs(Diphoton_LeadEta)<1.5660)||(fabs(Diphoton_SubLeadEta)>1.4442&&fabs(Diphoton_SubLeadEta)<1.566)) 
       &&//Demand that both photons are gen-matched with real ones by asking GenGaGaFlag>=2`
       (Diphoton_LeadIsGenMatched>0 && Diphoton_SubLeadIsGenMatched>0) 
       &&//Demand that both photons pass the MIT Preselection
       (Diphoton_LeadMITPre>0&&Diphoton_SubLeadMITPre>0)
       &&//both photonIDMVA outputs are above the loose cut
       (Diphoton_LeadMVAOutput>-0.2&&Diphoton_SubLeadMVAOutput>-0.2)
       &&//diphotonMVA output is also above the minimum cut
       (Diphoton_MVAOutput>-0.78);
     fillhisto[2]=fillhisto[1]&&(Diphoton_LeadHasPixSeed&&Diphoton_SubLeadHasPixSeed);//Denominator haspixelseed study //Temporary
     fillhisto[3]=fillhisto[2]&&(bit194||bit195||bit205);//Numerator haspixelseed study //Temporary
     fillhisto[4]=fillhisto[1]&&(bit194||bit195||bit205);//Numerator study;
     fillhisto[5]=false; //Future Studies
     fillhisto[6]=false; //Future Studies
     
     /*event_hlt_bit.bit24;
       event_hlt_bit.bit25 
       event_hlt_bit.bit35;*/
     
     /*
     std::cout<<"fillhisto2 ";
     for(selection=0;selection<7  ;selection++){
       std::cout<<fillhisto[selection]<<" ";
     }
     std::cout<<std::endl;
     */
     
     for(selection=0;selection<7  ;selection++){ //Loop over the different histograms                                                               
       if(fillhisto[selection]){ //all hitograms below will be filled up if the boolean is true.                                                             
	 phi1phi2[selection]->Fill(Diphoton_LeadPhi,Diphoton_SubLeadPhi);
	 eta1eta2[selection]->Fill(Diphoton_LeadEta,Diphoton_SubLeadEta);
	 pt1pt2[selection]->Fill(Diphoton_LeadEt,Diphoton_SubLeadEt);
	 pt1pt2Norm[selection]->Fill(Diphoton_LeadEt/Diphoton_Mass,Diphoton_SubLeadEt/Diphoton_Mass);
	 wide_pt1pt2[selection]->Fill(Diphoton_LeadEt,Diphoton_SubLeadEt);
	 higgsEta[selection]->Fill(Diphoton_Eta);
	 higgsPhi[selection]->Fill(Diphoton_Phi);
	 higgsP[selection]->Fill(Diphoton_PT);                                                                      
	 higgsPt[selection]->Fill(Diphoton_PT);
	 ptLead[selection]->Fill(Diphoton_LeadEt);
	 ptTrail[selection]->Fill(Diphoton_SubLeadEt);
	 ptLeadNorm[selection]->Fill(Diphoton_LeadEt/Diphoton_Mass);
	 ptTrailNorm[selection]->Fill(Diphoton_SubLeadEt/Diphoton_Mass);
	 massHiggshisto[selection]->Fill(Diphoton_Mass);
	 massDiphotonhisto[selection]->Fill(Diphoton_Mass);
       }
     }
     //jentry=nentries;
   }

   //endjob
   
   std::cout<<"beginning endJob"<<std::endl;
   theFileOut->cd();
   for(selection=0;selection<7  ;selection++){ //Loop over the different histograms                                                                    
     ptLead[selection]->Write();
     ptTrail[selection]->Write();
     ptLeadNorm[selection]->Write();
     ptTrailNorm[selection]->Write();
     massDiphotonhisto[selection]->Write();
     massHiggshisto[selection]->Write();
     higgsEta[selection]->Write();
     higgsPhi[selection]->Write();
     higgsP[selection]->Write();
     higgsPt[selection]->Write();
     phi1phi2[selection]->Write();
     eta1eta2[selection]->Write();
     pt1pt2[selection]->Write();
     pt1pt2Norm[selection]->Write();
     wide_pt1pt2[selection]->Write();
   }
   theFileOut->Close();
  
}

