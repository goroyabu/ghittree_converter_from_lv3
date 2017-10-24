/*
2017/09/26 modified by Goro Yabu : event selection in Odaka mthesis is adopted 
*/
#ifndef HittreeLv3_Reader_H
#define HittreeLv3_Reader_H
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
class HittreeLv3Reader{
 private:
  const static Int_t N_SIGNAL_MAX = 256*5;
  TString fFileName;
  TFile * fFile;
  TTree * fTree;
  Long64_t fNentries,fReadEntry;

  Int_t f_nhit;
  Int_t f_detid_lv3[N_SIGNAL_MAX];
  Int_t f_detector_material_lv3[N_SIGNAL_MAX];
  Double_t f_pos_x_lv3[N_SIGNAL_MAX];
  Double_t f_pos_y_lv3[N_SIGNAL_MAX];
  Double_t f_pos_z_lv3[N_SIGNAL_MAX];
  Double_t f_delta_x_lv3[N_SIGNAL_MAX];
  Double_t f_delta_y_lv3[N_SIGNAL_MAX];
  Double_t f_delta_z_lv3[N_SIGNAL_MAX];
  Double_t f_epi_lv3[N_SIGNAL_MAX];

  void LoadFile();
  void SetBranch();
  
 public:
  HittreeLv3Reader(const TString inputfilename);
  ~HittreeLv3Reader();

  TString GetFileName() const {return fFileName;}
  TFile * GetFile() const {return fFile;}
  TTree * GetTree() const {return fTree;}
  Int_t GetEntry(const Long64_t i) {
    fReadEntry = i;
    return fTree->GetEntry(fReadEntry);}
  Long64_t GetEntries() const {return fNentries;}
  Int_t GetNhit() const {return f_nhit;}
  Int_t GetDetIDLv3(Int_t i) const {return f_detid_lv3[i];}
  Int_t GetDetectorMaterialLv3(Int_t i) const {return f_detector_material_lv3[i];}
  Double_t GetPosXLv3(Int_t i) const {return f_pos_x_lv3[i];}
  Double_t GetPosYLv3(Int_t i) const {return f_pos_y_lv3[i];}
  Double_t GetPosZLv3(Int_t i) const {return f_pos_z_lv3[i];}
  Double_t GetDeltaXLv3(Int_t i) const {return f_delta_x_lv3[i];}
  Double_t GetDeltaYLv3(Int_t i) const {return f_delta_y_lv3[i];}
  Double_t GetDeltaZLv3(Int_t i) const {return f_delta_z_lv3[i];}
  Double_t GetEpiLv3(Int_t i) const {return f_epi_lv3[i];}

  Int_t GetDetectorLv3(Int_t i) const {return GetDetIDLv3(i);}
};
#endif
  

