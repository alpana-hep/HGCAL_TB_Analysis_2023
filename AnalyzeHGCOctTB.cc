#define AnalyzeHGCOctTB_cxx
#include <iostream>
#include <vector>
#include <cstring>
#include "AnalyzeHGCOctTB.h"
#include "Math/SMatrix.h"
#include "Math/SVector.h"
#include <math.h>
#include<TF1.h>
using namespace std;



// chip 3022,44,3028




int main(int argc, char* argv[])//, int argvv[])
{

  if (argc < 5) {
    cerr << "Please give 5 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" <<" " << "run number" 
	 <<" " << "energy" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];
  const char *runNumber          = argv[4];
  const char *energy = argv[5];
  AnalyzeHGCOctTB hgcOctTB(inputFileList, outFileName, data, runNumber, energy);
  cout << "dataset " << data << " " << endl;
  cout << "run number " << runNumber << " " << endl;
  cout << "energy  " << energy << " " << endl;
  //int chi2_method = atoi(energy);
  hgcOctTB.EventLoop(data,energy);
  return 0;
}

void AnalyzeHGCOctTB::EventLoop(const char *data, const char *energy) {


  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t hgc_jentry = 0;

  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  Long64_t nbytes2 = 0, nb2 = 0;
  Long64_t nbytes3 = 0, nb3 = 0;

  

  int decade = 0;


  bool Debug = false;
  // //  bool DEBUG = true;
  // int TOTAL_ACTIVE_LAYER = -1;
  // int EE_LAYER = -1;
  // int FH_LAYER = -1;
  // int AH_LAYER = -1;
  // if(!strcmp(conf_,"alpha") || !strcmp(conf_,"config1")) {
  //   TOTAL_ACTIVE_LAYER = 79;
  //   EE_LAYER = 28;
  //   FH_LAYER = 12;
  //   AH_LAYER = 39;
  // }
  // else if(!strcmp(conf_,"bravo") || !strcmp(conf_,"config2")){
  //   TOTAL_ACTIVE_LAYER = 78;
  //   EE_LAYER = 28;
  //   FH_LAYER = 11;
  //   AH_LAYER = 39;
  // }
  // else if(!strcmp(conf_,"charlie") || !strcmp(conf_,"config3")) {
  //   TOTAL_ACTIVE_LAYER = 59;
  //   EE_LAYER = 8;
  //   FH_LAYER = 12;
  //   AH_LAYER = 39;
    
  // }
  // else {
  //   cout<<"ERROR: Unknown configuration!!!!"<<endl;
  //   return;
  // }
  // char * hname = new char[100];
  // sprintf(hname,"output2.txt");
  // std::ofstream file_i;
  // file_i.open(hname,ios::out);

  if(Debug)
    nentries=1;
  //  nentries=100;
  Long64_t jentry;
  for (jentry=0; jentry<nentries;jentry++,hgc_jentry++)
  {
    //   for (jentry=0; jentry<10000;jentry++,hgc_jentry++) {
    // ==============print number of events done == == == == == == == =
      double progress = 10.0 * jentry / (1.0 * nentries);
      int k = int (progress);
      if (k > decade)
	cout << 10 * k << " %" << endl;
      decade = k;
    
      // ===============read this entry == == == == == == == == == == ==

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) { break; cout<<"Breaking"<<endl;}
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      for (int ii=0;ii<nHGC;ii++)
        {
	  //if(HGC_id_halfrocChannel[ii]==24 && HGC_id_EconDeRx[ii]==0){ // && HGC_id_eleID[ii]==25 && !HGC_id_elecIDisCM[ii] && HGC_u_wafer[ii]==0 && HGC_v_wafer[ii]==0){
	  //if(Debug && HGC_layer[ii]==1)
	  //cout<<"Events "<<jentry<<"\t"<<HGC_id_eleID[ii]<<"\t"<<HGC_id_elecIDisCM[ii]<<"\t"<< HGC_u_wafer[ii]<<"\t"<<HGC_v_wafer[ii]<<"\t"<<HGC_layer[ii]<<"\t"<<HGC_id_EconDeRx[ii]<<"\t"<<HGC_id_EconDIdx[ii]<<endl;
	  if(HGC_energy[ii]>0)
	    h_HGC_energy->Fill(HGC_energy[ii]);
	  else	    
	    h_HGC_id_eleID_lt0_hgcEnergy->Fill(HGC_id_eleID[ii]);
	  //filling the ADC histograms
	  h_HGC_digi_adc->Fill(HGC_digi_adc[ii]);
	  h_HGC_digi_adcm1->Fill(HGC_digi_adcm1[ii]);
	  if(HGC_layer[ii]>2) continue;
	  // pedestal map
	  std::pair<int,int> chip_chan;
	  chip_chan = std::make_pair(HGC_id_EconDeRx[ii],HGC_id_halfrocChannel[ii]);
	  std::pair<int, std::pair<int,int>> layer_chip_chan;
	  layer_chip_chan = std::make_pair(HGC_layer[ii]-1,chip_chan);
	  std::pair<float, float> pedestal_noise;
	  //pedestal_noise = getNoise(layer_chip_chan);
	  int ADC_counts = HGC_digi_adc[ii];//-pedestal_noise.first; // for now, not subtracting the noise
	  //if(ADC_counts>5.0*pedestal_noise.second){
	  h_HGC_channelType[HGC_layer[ii]-1][HGC_id_EconDeRx[ii]][HGC_id_halfrocChannel[ii]]->Fill(HGC_id_elecIDisCM[ii]);
	  //cout<<"pedestal_noise.first " <<pedestal_noise.first<<"\t"<<pedestal_noise.second<<endl;
	  h_HGC_digi_adc_perChannel[HGC_layer[ii]-1][HGC_id_EconDeRx[ii]][HGC_id_halfrocChannel[ii]]->Fill(ADC_counts);//}
	  // int channleType = 0*(HGC_id_halfrocChannel[ii]<36)+1*(HGC_id_halfrocChannel[ii]==36) + 100* (HGC_id_halfrocChannel[ii]>36);
	  // int update_ch = (36*(HGC_id_EconDeRx[ii]%2) +HGC_id_halfrocChannel[ii])*(channleType==0)+(HGC_id_EconDeRx[ii]%2)*(channleType==1)+ ((HGC_id_halfrocChannel[ii]-37)+(HGC_id_EconDeRx[ii]%2)*2)*(channleType==100);
	  //file_i<<ii<<"\t"<<HGC_id_EconDeRx[ii]/2<<"\t"<<HGC_id_EconDeRx[ii]%2<<"\t"<<HGC_id_halfrocChannel[ii]<<"\t"<<HGC_id_halfrocChannel[ii]+(HGC_id_EconDeRx[ii]%2)*37<<"\t"<<update_ch<<"\t"<<channleType<<"\t"<<HGC_u_wafer[ii]<<"\t"<<HGC_v_wafer[ii]<<"\t"<<HGC_layer[ii]<<"\n";//<<HGC_u_cell[ii]<<"\t"<<HGC_v_cell[ii]<<"\t"<<HGC_layer[ii]<<"\n";
	  //	}	  
        }

  } // loop over entries
  

  ///////////////////////////////////////////////////////////
  ///////  E N D     O F     E N T R Y     L O O P     //////
  ///////////////////////////////////////////////////////////
  //  gSystem->Exit(0);
  cout<<"Got Out "<<jentry<<endl;
}
