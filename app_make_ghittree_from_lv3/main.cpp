/*
2017/09/22 written by Goro Yabu 
*/
#include "GHittreeMaker.h"
int main(int argc,char* argv[]){
  if(argc<1){
    cout << "Usage of app" << endl;
    cout << "[1] inputfile of hittree_lv3" << endl;
    return -1;
  }
  TString inname = argv[1];
  GHittreeMaker * gm = new GHittreeMaker(inname);
  gm->MakeTree();
}
