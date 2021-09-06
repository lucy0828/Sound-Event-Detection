//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPSender.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "UDPSender.h"
#include "release.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dspcodegen {
void UDPSender::SystemCore_delete()
{
  this->b_release();
}

//
// Arguments    : void
// Return Type  : void
//
void UDPSender::b_release()
{
  if (this->isInitialized == 1) {
    this->isInitialized = 2;
    this->releaseWrapper();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void UDPSender::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
    this->SystemCore_delete();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void UDPSender::releaseImpl()
{
  release(&this->cSFunObject);
}

//
// Arguments    : void
// Return Type  : void
//
void UDPSender::releaseWrapper()
{
  if (this->isSetupComplete) {
    this->releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : UDPSender
//
UDPSender::UDPSender()
{
  this->matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
UDPSender::~UDPSender()
{
  this->matlabCodegenDestructor();
}

} // namespace dspcodegen
} // namespace coder

//
// File trailer for UDPSender.cpp
//
// [EOF]
//
