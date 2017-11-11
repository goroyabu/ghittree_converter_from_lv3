#ifndef DualCCRotation_H
#define DualCCRotation_H
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TVector3.h"
#include <iostream>
using namespace std;
class DualCCRotation{
 private:
  Double_t fAngle;
  TVector3 fPosOrigin;
  TVector3 fPosRotate;
  
  void RotateVector();
  
 public:
  DualCCRotation(){fAngle = 0;}
  ~DualCCRotation(){}

  void SetVector(Double_t _x,Double_t _y,Double_t _z){fPosOrigin.SetXYZ(_x,_y,_z);this->RotateVector();}
  void SetAngle(Double_t _deg){fAngle = _deg;}
  Double_t GetX() const {return fPosRotate.X();}
  Double_t GetY() const {return fPosRotate.Y();}
  Double_t GetZ() const {return fPosRotate.Z();}
  Double_t GetXOrigin() const {return fPosOrigin.X();}
  Double_t GetYOrigin() const {return fPosOrigin.Y();}
  Double_t GetZOrigin() const {return fPosOrigin.Z();}
};
#endif
