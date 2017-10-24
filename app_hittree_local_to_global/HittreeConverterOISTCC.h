#ifndef HittreeConverterOISTCC_H
#define HittreeConverterOISTCC_H
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "DualCCTransformer.h"
class HittreeConverterOISTCC{
 private:
  const static Int_t kNsigmax = 256*5;
  TString fInFileName,fOutFileName;
  TFile * fInFile;
  TTree * fInTree;

  DualCCTransformer * fTF;
  
  TFile * fOutFile;
  TTree * fOutTree;
  TBranch *fBranchOldX, *fBranchOldY, *fBranchOldZ;
  TBranch *fBranchNewX, *fBranchNewY, *fBranchNewZ;

  Long64_t fNentries,fReadEntry;

  UInt_t f_ti,f_livetime,f_integral_livetime,f_unixtime;
  Int_t f_nhit,f_detid_lv3[kNsigmax],f_detector_material_lv3[kNsigmax];
  Double_t fOld_pos_x_lv3[kNsigmax],fOld_pos_y_lv3[kNsigmax],fOld_pos_z_lv3[kNsigmax];
  Double_t fOld_delta_x_lv3[kNsigmax],fOld_delta_y_lv3[kNsigmax],fOld_delta_z_lv3[kNsigmax];
  Double_t fNew_pos_x_lv3[kNsigmax],fNew_pos_y_lv3[kNsigmax],fNew_pos_z_lv3[kNsigmax];
  Double_t fNew_delta_x_lv3[kNsigmax],fNew_delta_y_lv3[kNsigmax],fNew_delta_z_lv3[kNsigmax];
  Double_t fLocal_pos_x_lv3[kNsigmax],fLocal_pos_y_lv3[kNsigmax],fLocal_pos_z_lv3[kNsigmax];
  Double_t f_epi_lv3[kNsigmax];

  void LoadFile();
  void MakeOutFile();
  void SetBranch();  
  void SetNewValue();
  void FillBranch();
  void Write();
  
 public:
  HittreeConverterOISTCC(const TString inputfilename);
  ~HittreeConverterOISTCC(){}
  void ConvertTree();

  Long64_t GetEntries() const {return fNentries;}
  UInt_t GetTi() const {return f_ti;}
  UInt_t GetLivetime() const {return f_livetime;}
  UInt_t GetIntegralLivetime() const {return f_integral_livetime;}
  UInt_t GetUnixtime() const {return f_unixtime;}
  Int_t GetNhit() const {return f_nhit;}
  Int_t GetDetID(const Int_t i) const {return f_detid_lv3[i];}
  Int_t GetDetectorMaterial(const Int_t i) const {return f_detector_material_lv3[i];}
  Double_t GetEpi(const Int_t i) const {return f_epi_lv3[i];}
};
#endif
