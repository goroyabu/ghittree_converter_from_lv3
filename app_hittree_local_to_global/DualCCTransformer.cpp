#include "DualCCTransformer.h"
const TString DualCCTransformer::kCamStr[] = {"cam1","cam2"};
const Double_t DualCCTransformer::kLocXaxis[] = {1.0,-1.0};
const Double_t DualCCTransformer::kLocYaxis[] = {-1.0,-1.0};
const Double_t DualCCTransformer::kLocZaxis[] = {1.0,-1.0};
const Double_t DualCCTransformer::kHorizontalZ[] = {-4.135,4.135};
const Double_t DualCCTransformer::kAngleXZ[] = {1.60*TMath::Pi()/180.0,0};//0.29*TMath::Pi()/180.0};
const Double_t DualCCTransformer::kAngleXY[] = {0.5*TMath::Pi()/180.0,0};
const Double_t DualCCTransformer::kVerticalY[] = {0.02,0.02}; 
DualCCTransformer::DualCCTransformer(TString inputfilename){
  fFileName = inputfilename;
  Setup();
}
DualCCTransformer::~DualCCTransformer(){
}

void DualCCTransformer::Setup(){
  string innamestr = (string)fFileName;
  if(innamestr.find(kCamStr[0])<innamestr.size()){
    fCamNum = 1;
    cout << "CAM_NUMBER = 1" << endl;
  }else if(innamestr.find(kCamStr[1])<innamestr.size()){
    fCamNum = 2;
    cout << "CAM_NUMBER = 2" << endl;
  }else{
    fCamNum = 1;
    cout << "NOT FOUND CAM_NUMBER : cam1 or cam2" << endl;
  }
}
void DualCCTransformer::SetVector(Double_t x0,Double_t y0,Double_t z0){
  fPosOrigin.SetXYZ(x0,y0,z0);
  TransformToGlobal();
  ApplyCalib();
}
void DualCCTransformer::TransformToGlobal(){
  if(fCamNum==1 || fCamNum==2){
    Double_t tempx,tempy,tempz;
    tempx = fPosOrigin.X()*kLocXaxis[fCamNum-1];
    tempy = fPosOrigin.Y()*kLocYaxis[fCamNum-1];
    tempz = fPosOrigin.Z()*kLocZaxis[fCamNum-1] + kHorizontalZ[fCamNum-1];
    fPosJustGlobal.SetXYZ(tempx,tempy,tempz);
  }
}
void DualCCTransformer::ApplyCalib(){
  if(fCamNum==1 || fCamNum==2){
    Double_t tempx,tempy,tempz;
    tempy = fPosJustGlobal.Y() + kVerticalY[fCamNum-1];
    tempx = fPosJustGlobal.X()*TMath::Cos(kAngleXZ[fCamNum-1])-fPosJustGlobal.Z()*TMath::Sin(kAngleXZ[fCamNum-1]);
    tempz = fPosJustGlobal.X()*TMath::Sin(kAngleXZ[fCamNum-1])+fPosJustGlobal.Z()*TMath::Cos(kAngleXZ[fCamNum-1]);
    
    Double_t temp2x,temp2y;
    temp2x = tempx*TMath::Cos(kAngleXY[fCamNum-1])-tempy*TMath::Sin(kAngleXY[fCamNum-1]);
    temp2y = tempx*TMath::Sin(kAngleXY[fCamNum-1])+tempy*TMath::Cos(kAngleXY[fCamNum-1]);
    
    fPosCalib.SetXYZ(temp2x,temp2y,tempz);
  }
}
