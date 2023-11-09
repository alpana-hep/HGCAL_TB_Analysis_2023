//#define mipFitterTree_cxx
#include "noiseFitter.h"

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLatex.h>
#include <sstream>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <iomanip>
// #include "helper.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooFFTConvPdf.h"
#include "RooDataHist.h"
#include "RooHist.h"
#include "RooCurve.h"
#include "RooFitResult.h"

using namespace RooFit;

//TFile* _file0 = TFile::Open("./out_reReco_Aug16_pedestal_1691518350.root");

ofstream myfile_all;
void Loop(int layer,int chip,int channel, int pos_, TFile* _file0,string pathname, TGraph* gr, TH1F* h_chi2)
{  
   TCanvas *cc;
   setTDRStyle();

   cc=new TCanvas();
   cc->SetWindowSize(850,750);
   cc->SetRightMargin(0.017);
   cc->SetLeftMargin(0.2);
  // cc->SetTopMargin(0.0657);
  // cc->SetBottomMargin(0.94);
  cc->SetRightMargin(0.017);
  cc->SetLeftMargin(0.17);
  // cc->SetTopMargin(0.0657);
  // cc->SetBottomMargin(0.94);


  bool saveCanvas_ = true;
   // if (print_draw) {
   //   setTDRStyle();
   // }

   char* hname = new char[500];
   char *det = new char[20];
   // sprintf(hanme,"ADC_distributions/EE%d/h_TS3HG_EE_L1_P0_chip3_chan40");
   if(pos_ == 0) {
     sprintf(hname,"h_HGC_digi_adc_chip_%d_channel_%d_Module_%d",chip,channel,layer);
     sprintf(det,"EE");
   }
   else {
     sprintf(hname,"h_HGC_digi_adc_chip_%d_channel_%d_Module_%d",chip,channel,layer);//ADC_distributions/FH_L%d_P%d/h_TS3HG_FH_L%d_P%d_chip%d_chan%d",layer,pos_,layer,pos_,chip,channel);
     sprintf(det,"FH");
   }
   TH1F* h = (TH1F*)_file0->Get(hname);
   if(!h) {
     cout<<"Could Not Load hist = "<<hname<<endl;
     return;
   }
   // if(h->GetEntries()==0)
   //   return;
   // return;
   // h->GetYaxis()->SetRangeUser(10,20);
   float h_mean = h->GetMean();
   cout<<" h->GetMean() "<<h->GetMean()<<"\t"<<"chip "<<chip<<"\t"<<"channel "<<channel<<" layer _ "<<layer<<endl;
   h->GetXaxis()->SetRangeUser(10,300);

   h->SetTitle("yolo");
   // TF1 *fit_gaus = new TF1("gauss","[0]*TMath::Gaus(x,[1],[2])",h->GetMean()-20,h->GetMean()+20);
   // h->Fit("gauss","ME");
   //   TF1* f3 = h->GetFunction("gauss");
   //   TF1 *f_l =  (TF1*)f3->Clone("f3");
   //  float chi2_ndf =0.0;
   //  float chi2 = f_l->GetChisquare();
   //  int Ndf = f_l->GetNDF();
   //  chi2_ndf = chi2/Ndf; //cout<<"\t"<<chi2_ndf<<"\t"<<"test"<<endl;
    RooRealVar x("x","ADC count (high gain)",10,220.0) ;

   RooArgList l = RooArgList(x);

   RooRealVar mean0("mean","Smearing mean (fixed at zero, no bias)",0,h->GetMean()-30,h->GetMean()+30) ;
   RooRealVar sigma0("SigmaG","Width of smearing gaussian",10,0,100.0) ;
   RooGaussian mipG0("smearing_gaus","Smearing gaussian",x,mean0,sigma0) ;  

   RooDataHist data("data", h->GetTitle(), l, h);
   RooPlot* xframe = x.frame(Name("xframe"),Title("YOLO ")) ;
   xframe->SetYTitle("Events");
   xframe->SetXTitle("ADC counts");
   xframe->GetYaxis()->SetTitleOffset(1.5) ; 
   xframe->SetTitle("yolo");
   data.plotOn(xframe) ;
   //mipG0.setStringAttribute("fitrange", nullptr);
   // mipG0.setStringAttribute("Range",h->GetMean()+2.0*h->GetRMS())
   // mipG0.setStringAttribute("NormRange",nullptr);
   RooFitResult* rfr = mipG0.fitTo(data,PrintLevel(-1),Save());
   //Range(h->GetMean()-2.0*h->GetRMS(),h->GetMean()+2.0*h->GetRMS()),PrintLevel(-1),Save());
   //   cout<<rfr->Chi2()<<endl;
   rfr->Print();//floatParsFinal().Print("s");
   //Double_t chi2 = frame->chiSquare(nFloatParam) ;
   mipG0.plotOn(xframe);

   mipG0.paramOn(xframe, 
   		 Layout(0.56, 0.98, 0.75), 
   		 Format("NELU", AutoPrecision(1)));
   //   RooArgSet* flparams = mipG0.getParameters(obs);//->selectByAttrib(“Constant”,kFALSE) ;
   //   int fParams = flparams->getSize();
   // Double_t chi2 = xframe->chiSquare("RooGaussian", "data", 2);
   // long fitnll = rfr->minNll();
   // cout<<"chi2 = “<<chi2<<” Nll = "<<fitnll<<endl;
   // Double_t chi2 = xframe->chiSquare(fParams) ;
   
   // out<< "chi2   "<<chi2<<"\t"<<"fparams  "<<fParams<<endl;
   //rfr->Print("V");

   xframe->Draw();
   //    RooDataSet* dsmall = (RooDataSet*) data.reduce(EventRange(1,100)) ;
   // RooDataHist* dhsmall = dsmall->binnedClone() ;
   //  RooChi2Var chi2_lowstat("chi2_lowstat","chi2",mipG0,data) ;
   // cout << chi2_lowstat.getVal() << endl ;

   Double_t chi2 = xframe->chiSquare(2);//"mipG0", "data", 0);
   long fitnll = rfr->minNll();
    cout<<"chi2 = "<< chi2<<" Nll = "<<fitnll<<endl;

   std::ostringstream os(std::ostringstream::ate);   
   os.str("");
   os<<"Layer="<<layer<<" Chip="<<chip<<" Channel="<<channel;

   TLatex *tex=new TLatex();
   tex->SetTextColor(kBlack);
   tex->SetTextSize(0.041);
   cout<< "os = "<<os.str()<<endl;
   tex->DrawLatexNDC(0.15,0.96,os.str().c_str());
   gPad->SetGridx();
   gPad->SetGridy();
      gPad->SetLogy();
   cc->Update();     
   // if(saveCanvas_) {
   //   char* canvas_name = new char[200];
   //   if(layer < 10)
   //     sprintf(canvas_name,"plots/Run_pedestal_1691518350_ReRecoAug16/layer%d_chip%d_channel%d.png",layer,chip,channel);
   //   // else 
   //   //   sprintf(canvas_name,"plots/v12LG/%s_layer_%d_P%d/layer%d_P%d_chip%d_channel%d.gif",det,layer,pos_,layer,pos_,chip,channel);
   //   cc->SaveAs(canvas_name);
   // }

   double mean = mean0.getValV();
   int entries = h->GetEntries();
   double sigma = sigma0.getValV();
   double err_sig = sigma0.getError();
   double err_mean = mean0.getError();
    char* line = new char[1000];
   //FOR EE
   //sprintf(line,"%d %d %d %d %.3f %.3f %.3f\n",layer,chip,channel,entries,mean,sigma,err_sig);

   //FOR FH
 
   int update_channel = chip*36+channel;
   int NRoc_chip = chip/2;
   int  halfRoc_chip = chip%2;
   // int channel_type =0*(channel<36)+ 1*(channel==36) + 100* (channel>36);
   // int Map_channel = (37*halfRoc_chip + channel)*(channel_type==0) + (halfRoc_chip*(channel_type==1))+ ((channel-36)+halfRoc_chip*2)*(channel_type==100);
   int global_chID = 78*NRoc_chip+39*halfRoc_chip+channel;
   //   cout<<global_chID<<"\t"<<chi2_ndf<<"\t"<<"test"<<endl;
   h_chi2->Fill(chi2);
   if(chi2>500)
     gr->SetPoint(global_chID,global_chID,chi2);
   if(saveCanvas_) {
     char* canvas_name = new char[200];
     if(layer < 10)
       sprintf(canvas_name,"%slayer%d_chip%d_channel%d.png",pathname.c_str(),layer,chip,channel);
     
     cc->SaveAs(canvas_name);
   }
      sprintf(line,"%d %d %d %d %d %d %.3f %.3f %.3f %.3f %.3f %.3f\n",layer,global_chID, NRoc_chip,halfRoc_chip,channel,entries,mean,sigma,err_mean,err_sig,h_mean,chi2);
      //sprintf(line,"%d %d %d %d %d %d %.3f\n",layer,global_chID, NRoc_chip,halfRoc_chip,channel,entries,chi2_ndf);
   //   counter++;
   cout<<line<<endl;
    myfile_all << line;


}
void for_all(string filename, string pathname, string output_text){
  TFile* _file0 = TFile::Open(filename.c_str());//"./out_reReco_Aug16_pedestal_1691518350.root");
  int layer_start = 0;
  int layer_end = 1;
  int counter=0;
  char* name = new char[100];
  sprintf(name,"%s.root",output_text.c_str());
  TFile*  fout = new TFile(name,"RECREATE");
  myfile_all.open(output_text.c_str());
  //Layer pos_ Chip channel entries mean sigma error_on_sigma
   char* line_ = new char[1000];
   sprintf(line_,"v1chi2_ndf_%s",output_text.c_str());
   TGraph *gr = new TGraph();
    gr->SetName(line_);
    gr->GetXaxis()->SetTitle("channel ID");
    gr->GetYaxis()->SetTitle("#chi^{2}/n.d.f");

  // sprintf(line_,"layer ")
    sprintf(line_,"chi2_ndf_%s",output_text.c_str());

    TH1F* h_chi2 = new TH1F(line_,"#chi^{2}/n.d.f",500,0,1000);
  for(int ilayer = layer_start; ilayer <= layer_end; ilayer++){
    for(int chip = 0; chip < 6; chip++){
      for(int channel = 0; channel < 39; channel++) {
	//	if(channel==8 ||channel==17 || channel ==18 || channel==19  || channel ==28) continue;
	counter++;
	Loop(ilayer,chip,channel,0,_file0, pathname.c_str(),gr, h_chi2);
	//counter++;
	//return;
      }
    }
  }

  cout<<"counter "<<counter<<endl;
  myfile_all.close();
 auto  cc=new TCanvas();
  cc->SetWindowSize(850,750);
  cc->SetRightMargin(0.017);
  cc->SetLeftMargin(0.2);
 cc->SetRightMargin(0.017);
 cc->SetLeftMargin(0.17);
 char* canvas_name = new char[200];
 // gr->GetYaxis()->SetRangeUser(5,00);
 gr->SetMarkerSize(1.5);
 gr->SetMarkerStyle(23);
 gr->SetLineColor(kBlue);
 gr->SetMarkerColor(kBlue);
 gr->Draw("AP");
 sprintf(canvas_name,"%s/%s.png",pathname.c_str(),line_);
 cc->SaveAs(canvas_name);
 sprintf(canvas_name,"%s/%s.pdf",pathname.c_str(),line_);
 cc->SaveAs(canvas_name);
 gPad->SetLogy();
 cc->Update();
 h_chi2->Draw("");
 sprintf(canvas_name,"%s/hist_%s.png",pathname.c_str(),line_);
 cc->SaveAs(canvas_name);
 sprintf(canvas_name,"%s/hist_%s.pdf",pathname.c_str(),line_);
 cc->SaveAs(canvas_name);

 fout->cd();
 h_chi2->Write();
 gr->Write();
 fout->Close();
 

}


// void for_all_FH(){
//   int layer_start = 1;
//   int layer_end = 12;
//   myfile_all.open("./Pedestal_noise_FH_LowGain.txt");
//   //Layer pos_ Chip channel entries mean sigma error_on_sigma
//   // char* line_ = new char[1000];
//   // sprintf(line_,"layer ")
//   for(int ilayer = layer_start; ilayer <= layer_end; ilayer++){
//     for(int ipos = 1; ipos <= 7 ; ipos++) {
//       for(int chip = 0; chip < 4; chip++){
// 	for(int channel = 0; channel < 64; channel+=2) {
// 	  if(ilayer > 9 && ipos != 4) continue;
// 	  Loop(ilayer,chip,channel,ipos);
// 	  //return;
// 	}
// 	// myfile_all.close();
//   	// return;
//       }
//     }
//   }
//   myfile_all.close();
// }

