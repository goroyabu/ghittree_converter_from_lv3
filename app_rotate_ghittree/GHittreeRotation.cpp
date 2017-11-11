#include "GHittreeRotation.h"
GHittreeRotation::GHittreeRotation(const TString _inname,const Double_t _angle){
  fInFileName = _inname;
  fAngle = _angle;

  fConverter = new DualCCRotation();
  fConverter->SetAngle(fAngle);
  
  LoadFile();
  MakeOutFile();
  SetBranch();
}
void GHittreeRotation::LoadFile(){
  fInFile = new TFile(fInFileName,"read");
  fInTree = (TTree*)fInFile->Get("ghittree");
  fNentries = fInTree->GetEntries();
}
void GHittreeRotation::MakeOutFile(){
  fOutFileName = Form("deg%1.f_rotate_"+fInFileName,fAngle);
  fOutFile = new TFile(fOutFileName,"recreate");
  cout << "OutFileName is " << fOutFileName << endl;
}
void GHittreeRotation::SetBranch(){
  fInTree->SetBranchStatus("hit*_pos*",0);
  fOutTree = (TTree*)fInTree->CloneTree(0);

  for(Int_t ihit=0;ihit<3;ihit++){
    fOutTree->Branch(Form("hit%d_posx",ihit+1),&fNew_hit_posx[ihit],Form("hit%d_posx/F",ihit+1));
    fOutTree->Branch(Form("hit%d_posy",ihit+1),&fNew_hit_posy[ihit],Form("hit%d_posy/F",ihit+1));
    fOutTree->Branch(Form("hit%d_posz",ihit+1),&fNew_hit_posz[ihit],Form("hit%d_posz/F",ihit+1));
  }

  fInTree->SetBranchStatus("hit*_pos*",1);
  for(Int_t ihit=0;ihit<3;ihit++){
    fInTree->SetBranchAddress(Form("hit%d_posx",ihit+1),&fOld_hit_posx[ihit]);
    fInTree->SetBranchAddress(Form("hit%d_posx",ihit+1),&fOld_hit_posx[ihit]);
    fInTree->SetBranchAddress(Form("hit%d_posx",ihit+1),&fOld_hit_posx[ihit]);
  }
}
void GHittreeRotation::SetNewValue(){
  for(Int_t ihit=0;ihit<3;ihit++){
    fConverter->SetVector(fOld_hit_posx[ihit],fOld_hit_posy[ihit],fOld_hit_posz[ihit]);
    fNew_hit_posx[ihit] = fConverter->GetX();
    fNew_hit_posy[ihit] = fConverter->GetY();
    fNew_hit_posz[ihit] = fConverter->GetZ();
  }
}
void GHittreeRotation::Write(){
  fOutFile->cd();
  fOutTree->Write();
  fOutFile->Close();
}
void GHittreeRotation::ConvertTree(){
  for(Long64_t i=0;i<fNentries;i++){
    fInTree->GetEntry(i);
    SetNewValue();
    fOutTree->Fill();
    if(i%100000==0)cout << i << "/" << fNentries << endl;
  }
  Write();
}
