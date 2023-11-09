//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 21 10:27:29 2023 by ROOT version 6.24/08
// from TTree Events/Events
// found on file: Pedestal/Run_-1691491176/26db19ec-35eb-11ee-b530-b8ca3af74182/Run1691491176_Run1691491176_Link2_File0000000000_NANO.root
//////////////////////////////////////////////////////////

#ifndef HGCNtupleVariables_h
#define HGCNtupleVariables_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class HGCNtupleVariables {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
 HGCNtupleVariables(TTree * /*tree*/ =0) : fChain(0) { }
   ~HGCNtupleVariables() { }
   void    Init(TTree *tree); 
   Bool_t  Notify();
   Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }

   std::map<std::pair<int,std::pair<int,int>>, std::pair<float, float> > noise_map;
   std::pair<float, float>  getNoise(std::pair<int,std::pair<int,int>>);//std::pair<int,int> mod_chip);
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   UInt_t          bunchCrossing;
   Int_t           nHGC;
   Int_t           HGC_detId[384];   //[nHGC]
   Float_t         HGC_energy[384];   //[nHGC]
   Float_t         HGC_time[384];   //[nHGC]
   UChar_t         hgcMetadata_injgain;
   UInt_t          hgcMetadata_trigType;
   UInt_t          hgcMetadata_trigTime;
   UInt_t          hgcMetadata_trigWidth;
   UInt_t          hgcMetadata_injcalib;
   UShort_t        HGC_digi_tctp[384];   //[nHGC]
   UInt_t          HGC_id_eleID[384];   //[nHGC]
   UInt_t          HGC_id_EconDIdx[384];   //[nHGC]
   UInt_t          HGC_id_EconDeRx[384];   //[nHGC]
   UInt_t          HGC_id_halfrocChannel[384];   //[nHGC]
   UInt_t          HGC_id_elecIDisCM[384];   //[nHGC]
   Float_t         HGC_digi_toa[384];   //[nHGC]
   Float_t         HGC_digi_tot[384];   //[nHGC]
   Float_t         HGC_digi_adc[384];   //[nHGC]
   Float_t         HGC_digi_adcm1[384];   //[nHGC]
   Int_t           HGC_u_wafer[384];   //[nHGC]
   Int_t           HGC_v_wafer[384];   //[nHGC]
   Int_t           HGC_u_cell[384];   //[nHGC]
   Int_t           HGC_v_cell[384];   //[nHGC]
   Int_t           HGC_zside[384];   //[nHGC]
   Int_t           HGC_siThickIndex[384];   //[nHGC]
   UInt_t          HGC_layer[384];   //[nHGC]
   Float_t         HGC_eta[384];   //[nHGC]
   Float_t         HGC_phi[384];   //[nHGC]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_bunchCrossing;   //!
   TBranch        *b_nHGC;   //!
   TBranch        *b_HGC_detId;   //!
   TBranch        *b_HGC_energy;   //!
   TBranch        *b_HGC_time;   //!
   TBranch        *b_hgcMetadata_injgain;   //!
   TBranch        *b_hgcMetadata_trigType;   //!
   TBranch        *b_hgcMetadata_trigTime;   //!
   TBranch        *b_hgcMetadata_trigWidth;   //!
   TBranch        *b_hgcMetadata_injcalib;   //!
   TBranch        *b_HGC_digi_tctp;   //!
   TBranch        *b_HGC_id_eleID;   //!
   TBranch        *b_HGC_id_EconDIdx;   //!
   TBranch        *b_HGC_id_EconDeRx;   //!
   TBranch        *b_HGC_id_halfrocChannel;   //!
   TBranch        *b_HGC_id_elecIDisCM;   //!
   TBranch        *b_HGC_digi_toa;   //!
   TBranch        *b_HGC_digi_tot;   //!
   TBranch        *b_HGC_digi_adc;   //!
   TBranch        *b_HGC_digi_adcm1;   //!
   TBranch        *b_HGC_u_wafer;   //!
   TBranch        *b_HGC_v_wafer;   //!
   TBranch        *b_HGC_u_cell;   //!
   TBranch        *b_HGC_v_cell;   //!
   TBranch        *b_HGC_zside;   //!
   TBranch        *b_HGC_siThickIndex;   //!
   TBranch        *b_HGC_layer;   //!
   TBranch        *b_HGC_eta;   //!
   TBranch        *b_HGC_phi;   //!

   /* HGCNtupleVariables(TTree *tree=0); */
   /* virtual ~HGCNtupleVariables(); */
   /* virtual Int_t    Cut(Long64_t entry); */
   /* virtual Int_t    GetEntry(Long64_t entry); */
   /* virtual Long64_t LoadTree(Long64_t entry); */
   /* virtual void     Init(TTree *tree); */
   /* virtual void     Loop(); */
   /* virtual Bool_t   Notify(); */
   /* virtual void     Show(Long64_t entry = -1); */
};

#endif

#ifdef HGCNtupleVariables_cxx
/* HGCNtupleVariables::HGCNtupleVariables(TTree *tree) : fChain(0)  */
/* { */
/* // if parameter tree is not specified (or zero), connect the file */
/* // used to generate this class and read the Tree. */
/*    if (tree == 0) { */
/*       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Pedestal/Run_-1691491176/26db19ec-35eb-11ee-b530-b8ca3af74182/Run1691491176_Run1691491176_Link2_File0000000000_NANO.root"); */
/*       if (!f || !f->IsOpen()) { */
/*          f = new TFile("Pedestal/Run_-1691491176/26db19ec-35eb-11ee-b530-b8ca3af74182/Run1691491176_Run1691491176_Link2_File0000000000_NANO.root"); */
/*       } */
/*       f->GetObject("Events",tree); */

/*    } */
/*    Init(tree); */
/* } */

/* HGCNtupleVariables::~HGCNtupleVariables() */
/* { */
/*    if (!fChain) return; */
/*    delete fChain->GetCurrentFile(); */
/* } */

/* Int_t HGCNtupleVariables::GetEntry(Long64_t entry) */
/* { */
/* // Read contents of entry. */
/*    if (!fChain) return 0; */
/*    return fChain->GetEntry(entry); */
/* } */
/* Long64_t HGCNtupleVariables::LoadTree(Long64_t entry) */
/* { */
/* // Set the environment to read one entry */
/*    if (!fChain) return -5; */
/*    Long64_t centry = fChain->LoadTree(entry); */
/*    if (centry < 0) return centry; */
/*    if (fChain->GetTreeNumber() != fCurrent) { */
/*       fCurrent = fChain->GetTreeNumber(); */
/*       Notify(); */
/*    } */
/*    return centry; */
/* } */

void HGCNtupleVariables::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("bunchCrossing", &bunchCrossing, &b_bunchCrossing);
   fChain->SetBranchAddress("nHGC", &nHGC, &b_nHGC);
   fChain->SetBranchAddress("HGC_detId", HGC_detId, &b_HGC_detId);
   fChain->SetBranchAddress("HGC_energy", HGC_energy, &b_HGC_energy);
   fChain->SetBranchAddress("HGC_time", HGC_time, &b_HGC_time);
   fChain->SetBranchAddress("hgcMetadata_injgain", &hgcMetadata_injgain, &b_hgcMetadata_injgain);
   fChain->SetBranchAddress("hgcMetadata_trigType", &hgcMetadata_trigType, &b_hgcMetadata_trigType);
   fChain->SetBranchAddress("hgcMetadata_trigTime", &hgcMetadata_trigTime, &b_hgcMetadata_trigTime);
   fChain->SetBranchAddress("hgcMetadata_trigWidth", &hgcMetadata_trigWidth, &b_hgcMetadata_trigWidth);
   fChain->SetBranchAddress("hgcMetadata_injcalib", &hgcMetadata_injcalib, &b_hgcMetadata_injcalib);
   fChain->SetBranchAddress("HGC_digi_tctp", HGC_digi_tctp, &b_HGC_digi_tctp);
   fChain->SetBranchAddress("HGC_id_eleID", HGC_id_eleID, &b_HGC_id_eleID);
   fChain->SetBranchAddress("HGC_id_EconDIdx", HGC_id_EconDIdx, &b_HGC_id_EconDIdx);
   fChain->SetBranchAddress("HGC_id_EconDeRx", HGC_id_EconDeRx, &b_HGC_id_EconDeRx);
   fChain->SetBranchAddress("HGC_id_halfrocChannel", HGC_id_halfrocChannel, &b_HGC_id_halfrocChannel);
   fChain->SetBranchAddress("HGC_id_elecIDisCM", HGC_id_elecIDisCM, &b_HGC_id_elecIDisCM);
   fChain->SetBranchAddress("HGC_digi_toa", HGC_digi_toa, &b_HGC_digi_toa);
   fChain->SetBranchAddress("HGC_digi_tot", HGC_digi_tot, &b_HGC_digi_tot);
   fChain->SetBranchAddress("HGC_digi_adc", HGC_digi_adc, &b_HGC_digi_adc);
   fChain->SetBranchAddress("HGC_digi_adcm1", HGC_digi_adcm1, &b_HGC_digi_adcm1);
   fChain->SetBranchAddress("HGC_u_wafer", HGC_u_wafer, &b_HGC_u_wafer);
   fChain->SetBranchAddress("HGC_v_wafer", HGC_v_wafer, &b_HGC_v_wafer);
   fChain->SetBranchAddress("HGC_u_cell", HGC_u_cell, &b_HGC_u_cell);
   fChain->SetBranchAddress("HGC_v_cell", HGC_v_cell, &b_HGC_v_cell);
   fChain->SetBranchAddress("HGC_zside", HGC_zside, &b_HGC_zside);
   fChain->SetBranchAddress("HGC_siThickIndex", HGC_siThickIndex, &b_HGC_siThickIndex);
   fChain->SetBranchAddress("HGC_layer", HGC_layer, &b_HGC_layer);
   fChain->SetBranchAddress("HGC_eta", HGC_eta, &b_HGC_eta);
   fChain->SetBranchAddress("HGC_phi", HGC_phi, &b_HGC_phi);
   Notify();
}

Bool_t HGCNtupleVariables::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

/* void HGCNtupleVariables::Show(Long64_t entry) */
/* { */
/* // Print contents of entry. */
/* // If entry is not specified, print current entry */
/*    if (!fChain) return; */
/*    fChain->Show(entry); */
/* } */
/* Int_t HGCNtupleVariables::Cut(Long64_t entry) */
/* { */
/* // This function may be called from Loop. */
/* // returns  1 if entry is accepted. */
/* // returns -1 otherwise. */
/*    return 1; */
/* } */
#endif // #ifdef HGCNtupleVariables_cxx
