//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: UDPReceiver.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

// Include Files
#include "rtwtypes.h"
#include "coder_bounded_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_UDPReceiver_1 {
  int S0_isInitialized;
  double W0_NetworkLib[137];
  int P0_Port;
  coder::bounded_array<float, 800U, 2U> O0_Y0;
};

namespace coder {
namespace dspcodegen {
class UDPReceiver {
public:
  void matlabCodegenDestructor();
  void b_release();
  void releaseWrapper();
  ~UDPReceiver();
  UDPReceiver();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  dsp_UDPReceiver_1 cSFunObject;
};

} // namespace dspcodegen
} // namespace coder

#endif
//
// File trailer for UDPReceiver.h
//
// [EOF]
//
