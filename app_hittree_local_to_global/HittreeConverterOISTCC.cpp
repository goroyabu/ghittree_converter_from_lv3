#include "HittreeConverterOISTCC.h"
HittreeConverterOISTCC::HittreeConverterOISTCC(TString inputfilename){
  fInFileName = inputfilename;
  fOutFileName = "global_"+fInFileName;
  TString tempname = fInFileName;
  fOutFileName = tempname.Remove(tempname.Sizeof()-17,16)+"globalhittree_lv3.root";
  
  fTF = new DualCCTransformer(fInFileName);
  LoadFile();
  MakeOutFile();
  SetBranch();
}

void HittreeConverterOISTCC::LoadFile(){
  fInFile = new TFile(fInFileName,"read");
  fInTree = (TTree*)fInFile->Get("hittree_lv3");
  fNentries = fInTree->GetEntries();
}
void HittreeConverterOISTCC::MakeOutFile(){
  fOutFile = new TFile(fOutFileName,"recreate");
}
void HittreeConverterOISTCC::SetBranch(){
  fInTree->SetBranchStatus("*",0);
  fInTree->SetBranchStatus("ti",1);
  fInTree->SetBranchStatus("livetime",1);
  fInTree->SetBranchStatus("integral_livetime",1);
  fInTree->SetBranchStatus("unixtime",1);
  fInTree->SetBranchStatus("nhit",1);
  fInTree->SetBranchStatus("detid_lv3",1);
  fInTree->SetBranchStatus("detector_material_lv3",1);
  fInTree->SetBranchStatus("delta_*_lv3",1);
  fInTree->SetBranchStatus("epi_lv3",1);
  fInTree->SetBranchAddress("ti",&f_ti);
  fInTree->SetBranchAddress("livetime",&f_livetime);
  fInTree->SetBranchAddress("integral_livetime",&f_integral_livetime);
  fInTree->SetBranchAddress("livetime",&f_livetime);
  fInTree->SetBranchAddress("nhit",&f_nhit);
  fInTree->SetBranchAddress("epi_lv3",&f_epi_lv3);
  
  fOutTree = (TTree*)fInTree->CloneTree(0);

  fInTree->SetBranchStatus("pos_*_lv3",1);
  fInTree->SetBranchAddress("pos_x_lv3",fOld_pos_x_lv3);
  fInTree->SetBranchAddress("pos_y_lv3",fOld_pos_y_lv3);
  fInTree->SetBranchAddress("pos_z_lv3",fOld_pos_z_lv3);
  
  fBranchNewX = (TBranch*)fOutTree->Branch("pos_x_lv3",fNew_pos_x_lv3,"pos_x_lv3[nhit]/D");
  fBranchNewY = (TBranch*)fOutTree->Branch("pos_y_lv3",fNew_pos_y_lv3,"pos_y_lv3[nhit]/D");
  fBranchNewZ = (TBranch*)fOutTree->Branch("pos_z_lv3",fNew_pos_z_lv3,"pos_z_lv3[nhit]/D");
  fBranchOldX = (TBranch*)fOutTree->Branch("local_pos_x_lv3",fLocal_pos_x_lv3,"local_pos_x_lv3[nhit]/D");
  fBranchOldY = (TBranch*)fOutTree->Branch("local_pos_y_lv3",fLocal_pos_y_lv3,"local_pos_y_lv3[nhit]/D");
  fBranchOldZ = (TBranch*)fOutTree->Branch("local_pos_z_lv3",fLocal_pos_z_lv3,"local_pos_z_lv3[nhit]/D");

}
void HittreeConverterOISTCC::SetNewValue(){
  for(Int_t ihit=0;ihit<f_nhit;ihit++){
    //cout << fOld_pos_x_lv3[ihit] << endl;
    fTF->SetVector(fOld_pos_x_lv3[ihit],fOld_pos_y_lv3[ihit],fOld_pos_z_lv3[ihit]);
    fNew_pos_x_lv3[ihit] = fTF->GetX();
    fNew_pos_y_lv3[ihit] = fTF->GetY();
    fNew_pos_z_lv3[ihit] = fTF->GetZ();
    fLocal_pos_x_lv3[ihit] = fOld_pos_x_lv3[ihit];
    fLocal_pos_y_lv3[ihit] = fOld_pos_y_lv3[ihit];
    fLocal_pos_z_lv3[ihit] = fOld_pos_z_lv3[ihit];
  }
}
void HittreeConverterOISTCC::FillBranch(){
  fOutTree->Fill();
  /*
  fBranchNewX->Fill();
  fBranchNewY->Fill();
  fBranchNewZ->Fill();
  fBranchOldX->Fill();
  fBranchOldY->Fill();
  fBranchOldZ->Fill();
  */
}
void HittreeConverterOISTCC::Write(){
  fOutFile->cd();
  fOutTree->Write();
  fOutFile->Close();
}
void HittreeConverterOISTCC::ConvertTree(){
  for(Long64_t i=0;i<fNentries;i++){
    fInTree->GetEntry(i);
    SetNewValue();
    FillBranch();
    if(i%100000==0)cout << i << "/" << fNentries << endl;
  }
  Write();
}
