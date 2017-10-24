#include "GHittreeMaker.h"
GHittreeMaker::GHittreeMaker(const TString inputfilename){
  fInFileName = inputfilename;
  string name = (string)fInFileName;
  size_t ht_first = name.find("hittree_lv3.root");
  if(ht_first<name.size()){
    name.replace(ht_first,16,"ghittree.root");
    fOutFileName = name;
  }else{
    TString namestem = ((TString)name).Remove(name.size()-5,5);
    fOutFileName = namestem + "_ghittree.root";
  }
  cout << "ghittree filename = " << fOutFileName << endl;
  MakeOutFile();
  SetTree();
}
GHittreeMaker::~GHittreeMaker(){
}

void GHittreeMaker::MakeOutFile(){
}
void GHittreeMaker::SetTree(){
  fReader = new HittreeLv3Reader(fInFileName);
  fInTree = (TTree*)fReader->GetTree();
  fNentries = fReader->GetEntries();

  fOutFile = new TFile(fOutFileName,"recreate");
  fOutTree = (TTree*)fInTree->CloneTree(0);

  fOutTree->SetNameTitle("ghittree","ghittree");
  fOutTree->Branch("num_hits",&f_num_hits,"num_hits/I");
  for(Int_t ihit=0;ihit<kNmax;ihit++){
    fOutTree->Branch(Form("hit%d_detector",ihit+1),&f_hit_detector[ihit],Form("hit%d_detector/S",ihit+1));
    fOutTree->Branch(Form("hit%d_energy",ihit+1),&f_hit_energy[ihit],Form("hit%d_energy/F",ihit+1));
    fOutTree->Branch(Form("hit%d_posx",ihit+1),&f_hit_posx[ihit],Form("hit%d_posx/F",ihit+1));
    fOutTree->Branch(Form("hit%d_posy",ihit+1),&f_hit_posy[ihit],Form("hit%d_posy/F",ihit+1));
    fOutTree->Branch(Form("hit%d_posz",ihit+1),&f_hit_posz[ihit],Form("hit%d_posz/F",ihit+1));
  }
  fOutTree->Branch("totalenergy",&f_totalenergy,"totalenergy/F");
}
bool GHittreeMaker::IsOver2Hit(){
  bool over2hit = false;
  if(fReader->GetNhit()==2 || fReader->GetNhit()==3)over2hit = true;
  return over2hit;
}
bool GHittreeMaker::IsCoinSiAndCdTe(){
  bool sihit = false;
  bool cdtehit = false;
  for(Int_t ihit=0;ihit<fReader->GetNhit();ihit++){
    Int_t material = fReader->GetDetectorMaterialLv3(ihit);
    if(material==1)cdtehit = true;
    else if(material==0)sihit = true;
  }
  return sihit*cdtehit; 
}
void GHittreeMaker::FillTree(){
  f_num_hits = fReader->GetNhit();
  for(Int_t ihit=0;ihit<f_num_hits;ihit++){
    f_hit_detector[ihit] = fReader->GetDetectorLv3(f_num_hits-ihit-1);
    f_hit_energy[ihit] = fReader->GetEpiLv3(f_num_hits-ihit-1);
    f_hit_posx[ihit] = fReader->GetPosXLv3(f_num_hits-ihit-1);
    f_hit_posy[ihit] = fReader->GetPosYLv3(f_num_hits-ihit-1);
    f_hit_posz[ihit] = fReader->GetPosZLv3(f_num_hits-ihit-1);
    f_totalenergy += fReader->GetEpiLv3(f_num_hits-ihit-1);
    
    //f_hit_detector[ihit] = fReader->GetDetectorLv3(ihit);
    //f_hit_energy[ihit] = fReader->GetEpiLv3(ihit);
    //f_hit_posx[ihit] = fReader->GetPosXLv3(ihit);
    //f_hit_posy[ihit] = fReader->GetPosYLv3(ihit);
    //f_hit_posz[ihit] = fReader->GetPosZLv3(ihit);
    //f_totalenergy += fReader->GetEpiLv3(ihit);
  }
  fOutTree->Fill();
  ClearBranch();
}
void GHittreeMaker::ClearBranch(){
  f_num_hits = 0;
  for(Int_t ihit=0;ihit<kNmax;ihit++){
    f_hit_detector[ihit] = 0;
    f_hit_energy[ihit] = 0;
    f_hit_posx[ihit] = 0;
    f_hit_posy[ihit] = 0;
    f_hit_posz[ihit] = 0;
  }
  f_totalenergy = 0;
}
void GHittreeMaker::Write(){
  fOutFile->cd();
  fOutTree->Write();
}
void GHittreeMaker::MakeTree(){
  fReadEntry = 0;
  while(fReadEntry<fNentries){
    fReader->GetEntry(fReadEntry);
    if(IsOver2Hit()&&IsCoinSiAndCdTe())FillTree();
    fReadEntry++;
    if(fReadEntry%100000==0)cout << fReadEntry << "/" << fNentries << endl;
  }
  cout << fReadEntry << "/" << fNentries << endl;
  Write();
}
