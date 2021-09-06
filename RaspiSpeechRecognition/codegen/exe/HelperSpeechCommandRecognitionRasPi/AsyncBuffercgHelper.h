//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffercgHelper.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef ASYNCBUFFERCGHELPER_H
#define ASYNCBUFFERCGHELPER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct cell_wrap_6 {
  unsigned int f1[8];
};

namespace coder {
namespace dsp {
namespace private_ {
class AsyncBuffercgHelper {
public:
  void matlabCodegenDestructor();
  void b_release();
  void releaseWrapper();
  ~AsyncBuffercgHelper();
  AsyncBuffercgHelper();

protected:
  void releaseImpl();

private:
  void SystemCore_delete();

public:
  bool matlabCodegenIsDeleted;
  int isInitialized;
  bool isSetupComplete;
  int NumChannels;
  float Cache[16001];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
  bool AsyncBuffercgHelper_isInitialized;

private:
  cell_wrap_6 inputVarSize[1];
};

} // namespace private_
} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffercgHelper.h
//
// [EOF]
//
