#ifndef GHittreeRotation_H
#define GHittreeRotation_H
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "DualCCRotation.h"
class GHittreeRotation{
 private:
  const static Int_t kNsigmax = 256*5;
  TString fInFileName,fOutFileName;
  TFile * fInFile;
  TTree * fInTree;

  Double_t fAngle;
  DualCCRotation * fConverter;

  TFile * fOutFile;
  TTree * fOutTree;
  Float_t fOld_hit_posx[3],fOld_hit_posy[3],fOld_hit_posz[3];
  Float_t fNew_hit_posx[3],fNew_hit_posy[3],fNew_hit_posz[3];

  Long64_t fNentries,fReadEntry;

  void LoadFile();
  void MakeOutFile();
  void SetBranch();
  void SetNewValue();
  void Write();
  
 public:
  GHittreeRotation(const TString _inname,const Double_t _angle);
  ~GHittreeRotation(){}
  void ConvertTree();
  
};
#endif
