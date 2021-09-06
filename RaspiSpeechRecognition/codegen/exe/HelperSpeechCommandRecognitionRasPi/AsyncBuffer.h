//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef ASYNCBUFFER_H
#define ASYNCBUFFER_H

// Include Files
#include "AsyncBuffercgHelper.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace dsp {
class AsyncBuffer {
public:
  void read(float out_data[], int *out_size);
  void matlabCodegenDestructor();
  ~AsyncBuffer();
  AsyncBuffer();
  bool matlabCodegenIsDeleted;
  private_::AsyncBuffercgHelper pBuffer;
};

} // namespace dsp
} // namespace coder

#endif
//
// File trailer for AsyncBuffer.h
//
// [EOF]
//
