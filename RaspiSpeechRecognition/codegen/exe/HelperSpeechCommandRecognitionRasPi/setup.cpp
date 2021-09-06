//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: setup.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "setup.h"
#include "UDPReceiver.h"
#include "UDPSender.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

// Function Declarations
namespace coder {
static void Terminate(dsp_UDPSender_0 *obj);

static void Terminate(dsp_UDPReceiver_1 *obj);

} // namespace coder

// Function Definitions
//
// Arguments    : dsp_UDPSender_0 *obj
// Return Type  : void
//
namespace coder {
static void Terminate(dsp_UDPSender_0 *obj)
{
  char *sErr;
  // System object Terminate function: dsp.UDPSender
  sErr = GetErrorBuffer(&obj->W0_NetworkLib[0U]);
  LibTerminate(&obj->W0_NetworkLib[0U]);
  if (*sErr != 0) {
    PrintError(sErr);
  }
  LibDestroy(&obj->W0_NetworkLib[0U], 1);
  DestroyUDPInterface(&obj->W0_NetworkLib[0U]);
}

//
// Arguments    : dsp_UDPReceiver_1 *obj
// Return Type  : void
//
static void Terminate(dsp_UDPReceiver_1 *obj)
{
  char *sErr;
  // System object Terminate function: dsp.UDPReceiver
  sErr = GetErrorBuffer(&obj->W0_NetworkLib[0U]);
  LibTerminate(&obj->W0_NetworkLib[0U]);
  if (*sErr != 0) {
    PrintError(sErr);
  }
  LibDestroy(&obj->W0_NetworkLib[0U], 0);
  DestroyUDPInterface(&obj->W0_NetworkLib[0U]);
}

//
// Arguments    : dsp_UDPSender_0 *obj
// Return Type  : void
//
void Destructor(dsp_UDPSender_0 *obj)
{
  // System object Destructor function: dsp.UDPSender
  Terminate(obj);
}

//
// Arguments    : dsp_UDPReceiver_1 *obj
// Return Type  : void
//
void Destructor(dsp_UDPReceiver_1 *obj)
{
  // System object Destructor function: dsp.UDPReceiver
  Terminate(obj);
}

} // namespace coder

//
// File trailer for setup.cpp
//
// [EOF]
//
