//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: release.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "release.h"
#include "UDPReceiver.h"
#include "UDPSender.h"
#include "setup.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

// Function Definitions
//
// Arguments    : dsp_UDPSender_0 *obj
// Return Type  : void
//
namespace coder {
void release(dsp_UDPSender_0 *obj)
{
  Destructor(obj);
}

//
// Arguments    : dsp_UDPReceiver_1 *obj
// Return Type  : void
//
void release(dsp_UDPReceiver_1 *obj)
{
  Destructor(obj);
}

} // namespace coder

//
// File trailer for release.cpp
//
// [EOF]
//
