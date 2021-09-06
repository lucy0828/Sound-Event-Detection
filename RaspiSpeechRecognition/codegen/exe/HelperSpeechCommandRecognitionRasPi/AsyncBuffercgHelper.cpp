//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "AsyncBuffercgHelper.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
namespace private_ {
void AsyncBuffercgHelper::SystemCore_delete()
{
  this->b_release();
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::b_release()
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
void AsyncBuffercgHelper::matlabCodegenDestructor()
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
void AsyncBuffercgHelper::releaseImpl()
{
  this->ReadPointer = 1;
  this->WritePointer = 2;
  this->CumulativeOverrun = 0;
  this->CumulativeUnderrun = 0;
  this->AsyncBuffercgHelper_isInitialized = false;
  this->NumChannels = -1;
}

//
// Arguments    : void
// Return Type  : void
//
void AsyncBuffercgHelper::releaseWrapper()
{
  if (this->isSetupComplete) {
    this->releaseImpl();
  }
}

//
// Arguments    : void
// Return Type  : AsyncBuffercgHelper
//
AsyncBuffercgHelper::AsyncBuffercgHelper()
{
  this->matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffercgHelper::~AsyncBuffercgHelper()
{
  this->matlabCodegenDestructor();
}

} // namespace private_
} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffercgHelper.cpp
//
// [EOF]
//
