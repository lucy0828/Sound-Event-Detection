//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPSender.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef UDPSENDER_H
#define UDPSENDER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_UDPSender_0 {
  int S0_isInitialized;
  double W0_NetworkLib[137];
  int P0_Port;
};

namespace coder {
namespace dspcodegen {
class UDPSender {
public:
  void matlabCodegenDestructor();
  void b_release();
  void releaseWrapper();
  ~UDPSender();
  UDPSender();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  dsp_UDPSender_0 cSFunObject;
};

} // namespace dspcodegen
} // namespace coder

#endif
//
// File trailer for UDPSender.h
//
// [EOF]
//
