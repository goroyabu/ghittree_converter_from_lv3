#include "HittreeConverterOISTCC.h"
int main(int argc, char* argv[]){
  if(argc<1){
    cout << "Usage of app" << endl;
    cout << "[1] inputfile of globalhittree_lv3" << endl;
    return -1;
  }
  TString inname = argv[1];
  HittreeConverterOISTCC * hc = new HittreeConverterOISTCC(inname);
  hc->ConvertTree();
}
