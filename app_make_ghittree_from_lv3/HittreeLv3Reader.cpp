#include "HittreeLv3Reader.h"
HittreeLv3Reader::HittreeLv3Reader(const TString inputfilename){
  fFileName = inputfilename;
  LoadFile();
  SetBranch();
}
HittreeLv3Reader::~HittreeLv3Reader(){
}

void HittreeLv3Reader::LoadFile(){
  fFile = new TFile(fFileName,"read");
  fTree = (TTree*)fFile->Get("hittree_lv3");
  fNentries = fTree->GetEntries();
  fReadEntry = 0;
}
void HittreeLv3Reader::SetBranch(){
  fTree->SetBranchStatus("*",0);
  fTree->SetBranchStatus("nhit",1);
  fTree->SetBranchStatus("*_lv3",1);
  fTree->SetBranchAddress("nhit",&f_nhit);
  fTree->SetBranchAddress("detid_lv3",f_detid_lv3);
  fTree->SetBranchAddress("detector_material_lv3",f_detector_material_lv3);
  fTree->SetBranchAddress("pos_x_lv3",f_pos_x_lv3);
  fTree->SetBranchAddress("pos_y_lv3",f_pos_y_lv3);
  fTree->SetBranchAddress("pos_z_lv3",f_pos_z_lv3);
  fTree->SetBranchAddress("delta_x_lv3",f_delta_x_lv3);
  fTree->SetBranchAddress("delta_y_lv3",f_delta_y_lv3);
  fTree->SetBranchAddress("delta_z_lv3",f_delta_z_lv3);
  fTree->SetBranchAddress("epi_lv3",f_epi_lv3);
}
