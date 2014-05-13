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
   TH1F * cutflow;
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
   TH2F * pt1pt2Zoom[7  ];
   TH2F * wide_pt1pt2[7  ];
   const Double_t bins[19]={5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,90,100,110};
   bool cut[7  ];
   //string arrayHLTpathsNames[442  ];
   bool filled_hlt_names;
   int cut_index;
   //beginJobs
   filled_hlt_names=false;
   theFileOut = new TFile("-fileout-", "RECREATE");
   TString name;

   cutflow = new TH1F ("cutflow","cutflow",7  ,-0.5.,6.5.);

   for(cut_index=0;cut_index<7  ;cut_index++){//Loop over the different histograms
     name = Form("ptLead_%d",cut_index);      ptLead[cut_index]            = new TH1F (name,name,100,0.,120.);
     name = Form("ptTrail_%d",cut_index);     ptTrail[cut_index]           = new TH1F (name,name,100,0.,120.);
     name = Form("ptLeadNorm_%d",cut_index);  ptLeadNorm[cut_index]        = new TH1F (name,name,100,0.,1.);
     name = Form("ptTrailNorm_%d",cut_index); ptTrailNorm[cut_index]       = new TH1F (name,name,100,0.,1.);
     name = Form("massDiphoton_%d",cut_index);massDiphotonhisto[cut_index] = new TH1F (name,name,100,60.,180.);
     name = Form("massHiggs_%d",cut_index);   massHiggshisto[cut_index]    = new TH1F (name,name,100,60.,180.);
     name = Form("higgsEta_%d",cut_index);    higgsEta[cut_index]          = new TH1F (name,name,100,-5,5);
     name = Form("higgsPhi_%d",cut_index);    higgsPhi[cut_index]          = new TH1F (name,name,180,-3.15,3.15);
     name = Form("higgsP_%d",cut_index);      higgsP[cut_index]            = new TH1F (name,name,500,0,1200);
     name = Form("higgsPt_%d",cut_index);     higgsPt[cut_index]           = new TH1F (name,name,500,0,1200);
     name = Form("phi1phi2_%d",cut_index);    phi1phi2[cut_index]          = new TH2F (name,name,180,-3.15,3.15,180,-3.15,3.15);
     name = Form("eta1eta2_%d",cut_index);    eta1eta2[cut_index]          = new TH2F (name,name,100,-5,5,100,-5,5);
     name = Form("pt1pt2_%d",cut_index);      pt1pt2[cut_index]            = new TH2F (name,name,100,0.,110.,100,0.,110.);
     name = Form("pt1pt2Norm_%d",cut_index);  pt1pt2Norm[cut_index]        = new TH2F (name,name,100,0.,1.,100,0.,1.);
     name = Form("pt1pt2Zoom_%d",cut_index);  pt1pt2Zoom[cut_index]        = new TH2F (name,name,20,0.3,0.5,20,0.2,0.4);
     name = Form("wide_pt1pt2_%d",cut_index); wide_pt1pt2[cut_index]       = new TH2F (name,name,19-1,bins,19-1,bins);
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
     //std::cout<<"cut1 ";
     
     for(cut_index=0;cut_index<7  ;cut_index++){
       cut[cut_index]=false;
       //std::cout<<cut[cut_index]<<" ";
     }
     //std::cout<<std::endl;

     bool bit194=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 194)!=event_hlt_bit->end());
     bool bit195=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 195)!=event_hlt_bit->end());
     bool bit205=(std::find(event_hlt_bit->begin(), event_hlt_bit->end(), 205)!=event_hlt_bit->end());
     
     /*
       bit_194_HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass60_v5
       bit_195_HLT_Photon26_R9Id85_OR_CaloId10_Iso50_Photon18_R9Id85_OR_CaloId10_Iso50_Mass70_v1
       bit_205_HLT_Photon36_R9Id85_OR_CaloId10_Iso50_Photon22_R9Id85_OR_CaloId10_Iso50_v5
     */
     

     bool hlt_bit;

     if(event_RunID==206859){
       //periodD
       hlt_bit=(bit195||bit205);
     }else{
       //periodABC
       hlt_bit=(bit194||bit195||bit205);
     }


     bool selection=  //html
       //Avoid Transition region //html
       !((fabs(Diphoton_LeadEta)>1.4442&&fabs(Diphoton_LeadEta)<1.5660)||(fabs(Diphoton_SubLeadEta)>1.4442&&fabs(Diphoton_SubLeadEta)<1.5660)) //html
       //html
       &&//Demand that both photons are gen-matched with real ones by asking GenGaGaFlag>=2`//html
       (Diphoton_LeadIsGenMatched>0 && Diphoton_SubLeadIsGenMatched>0)//html
       //html
       &&//Demand that both photons pass the MIT Precut_index//html
       (Diphoton_LeadMITPre>0&&Diphoton_SubLeadMITPre>0)//html
       //html
       &&//both photonIDMVA outputs are above the loose cut//html
       (Diphoton_LeadMVAOutput>-0.2&&Diphoton_SubLeadMVAOutput>-0.2)//html
       //html
       &&//diphotonMVA output is also above the minimum cut//html
       (Diphoton_MVAOutput>-0.78)//html
       ;//html
       //html
     cut[0]=true; //all minitree level just for reference.//html 
     //html
     cut[1]=selection;//bool for Numerator (cut_index) DENOMINATOR 21 //html
     cut[2]=cut[1]&&hlt_bit;//Numerator study without ptNormcuts NUMERATOR 21//html
     //html
     cut[3]=selection&&(Diphoton_LeadEt>33.333 && Diphoton_SubLeadEt>25.);//Adding Absolute pt cuts DENOMINATOR  43//html
     cut[4]=cut[3]&&hlt_bit;//Numerator study with ptNormcuts NUMERATOR 43//html
     //html
     cut[5]=selection&&(Diphoton_LeadEt/Diphoton_Mass>0.36 && Diphoton_SubLeadEt/Diphoton_Mass>0.25);//Adding Normalized pt cuts DENOMINATOR 65//html
     cut[6]=cut[5]&&hlt_bit; //Future Studies NUMERATOR 65//html
     
     /*
     event_hlt_bit.bit24;
     event_hlt_bit.bit25 
     event_hlt_bit.bit35;
     std::cout<<"cut2";
     for(cut_index=0;cut_index<7  ;cut_index++) std::cout<<cut[cut_index]<<" ";
     std::cout<<std::endl;
     */
     
     for(cut_index=0;cut_index<7  ;cut_index++){ //Loop over the different histograms                                                               
       if(cut[cut_index]){ //all hitograms below will be filled up if the boolean is true.                                                             
	 cutflow->Fill(cut_index);
	 phi1phi2[cut_index]->Fill(Diphoton_LeadPhi,Diphoton_SubLeadPhi);
	 eta1eta2[cut_index]->Fill(Diphoton_LeadEta,Diphoton_SubLeadEta);
	 pt1pt2[cut_index]->Fill(Diphoton_LeadEt,Diphoton_SubLeadEt);
	 pt1pt2Norm[cut_index]->Fill(Diphoton_LeadEt/Diphoton_Mass,Diphoton_SubLeadEt/Diphoton_Mass);
	 pt1pt2Zoom[cut_index]->Fill(Diphoton_LeadEt/Diphoton_Mass,Diphoton_SubLeadEt/Diphoton_Mass);
	 wide_pt1pt2[cut_index]->Fill(Diphoton_LeadEt,Diphoton_SubLeadEt);
	 higgsEta[cut_index]->Fill(Diphoton_Eta);
	 higgsPhi[cut_index]->Fill(Diphoton_Phi);
	 higgsP[cut_index]->Fill(Diphoton_PT);                                                                      
	 higgsPt[cut_index]->Fill(Diphoton_PT);
	 ptLead[cut_index]->Fill(Diphoton_LeadEt);
	 ptTrail[cut_index]->Fill(Diphoton_SubLeadEt);
	 ptLeadNorm[cut_index]->Fill(Diphoton_LeadEt/Diphoton_Mass);
	 ptTrailNorm[cut_index]->Fill(Diphoton_SubLeadEt/Diphoton_Mass);
	 massHiggshisto[cut_index]->Fill(Diphoton_Mass);
	 massDiphotonhisto[cut_index]->Fill(Diphoton_Mass);
       }
     }
     //jentry=nentries;
   }

   //endjob
   
   std::cout<<"beginning endJob"<<std::endl;
   theFileOut->cd();
   cutflow->Write();
   for(cut_index=0;cut_index<7  ;cut_index++){ //Loop over the different histograms                                                                    
     ptLead[cut_index]->Write();
     ptTrail[cut_index]->Write();
     ptLeadNorm[cut_index]->Write();
     ptTrailNorm[cut_index]->Write();
     massDiphotonhisto[cut_index]->Write();
     massHiggshisto[cut_index]->Write();
     higgsEta[cut_index]->Write();
     higgsPhi[cut_index]->Write();
     higgsP[cut_index]->Write();
     higgsPt[cut_index]->Write();
     phi1phi2[cut_index]->Write();
     eta1eta2[cut_index]->Write();
     pt1pt2[cut_index]->Write();
     pt1pt2Norm[cut_index]->Write();
     pt1pt2Zoom[cut_index]->Write();
     wide_pt1pt2[cut_index]->Write();
   }
   theFileOut->Close();
  
}

