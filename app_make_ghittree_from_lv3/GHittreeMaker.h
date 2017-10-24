#ifndef GHittree_Maker_H
#define GHittree_Maker_H
#include <iostream>
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "HittreeLv3Reader.h"
using namespace std;
class GHittreeMaker{
 private:
  static const Int_t kNmax = 3;
  HittreeLv3Reader * fReader;
  Long64_t fNentries;
  TString fInFileName;
  TTree * fInTree;
  Long64_t fReadEntry;

  TString fOutFileName;
  TFile * fOutFile;
  TTree * fOutTree;

  Int_t f_num_hits;
  Short_t f_hit_detector[kNmax];
  Float_t f_hit_energy[kNmax];
  Float_t f_hit_posx[kNmax],f_hit_posy[kNmax],f_hit_posz[kNmax];
  Float_t f_totalenergy;

  void SetTree();
  void MakeOutFile();
  bool IsOver2Hit();
  bool IsCoinSiAndCdTe();
  void FillTree();
  void ClearBranch();
  void Write();
  
 public:
  GHittreeMaker(const TString inputfilename);
  ~GHittreeMaker();
  void MakeTree();
};

#endif
