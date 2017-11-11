#include "DualCCRotation.h"
void DualCCRotation::RotateVector(){
  fPosRotate = fPosOrigin;
  fPosRotate.RotateY(fAngle);
}
