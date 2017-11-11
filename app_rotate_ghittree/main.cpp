#include "GHittreeRotation.h"
int main(int argc,char* argv[]){
  if(argc<3){
    return -1;
  }

  TString inname = argv[1];
  Double_t angle = atof(argv[2]);

  GHittreeRotation * gr = new GHittreeRotation(inname,angle);
  gr->ConvertTree();
}
