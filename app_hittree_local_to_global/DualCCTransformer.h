/*
2017/09/01 modified by Goro Yabu 
*/
#ifndef DualCCTransformer_H
#define DualCCTransformer_H
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TVector3.h"
#include <iostream>
using namespace std;
class DualCCTransformer{
 private:
  TString fFileName;
  Int_t fCamNum;  
  TVector3 fPosOrigin;
  TVector3 fPosJustGlobal;
  TVector3 fPosCalib;

  void Setup();
  void TransformToGlobal();
  void ApplyCalib();
  
 public:
  const static TString kCamStr[2];
  const static Double_t kLocXaxis[2];
  const static Double_t kLocYaxis[2];
  const static Double_t kLocZaxis[2];
  const static Double_t kHorizontalZ[2];
  const static Double_t kAngleXZ[2];
  const static Double_t kAngleXY[2];
  const static Double_t kVerticalY[2];
  DualCCTransformer(const TString inputfilename);
  ~DualCCTransformer();

  void SetVector(Double_t x0,Double_t y0,Double_t z0);
  Double_t GetX() const {return fPosCalib.X();}
  Double_t GetY() const {return fPosCalib.Y();}
  Double_t GetZ() const {return fPosCalib.Z();}
  Double_t GetNotCalibX() const {return fPosJustGlobal.X();}
  Double_t GetNotCalibY() const {return fPosJustGlobal.Y();}
  Double_t GetNotCalibZ() const {return fPosJustGlobal.Z();}
};
#endif
