//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: AsyncBuffer.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "AsyncBuffer.h"
#include "AsyncBuffercgHelper.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace coder {
namespace dsp {
void AsyncBuffer::matlabCodegenDestructor()
{
  if (!this->matlabCodegenIsDeleted) {
    this->matlabCodegenIsDeleted = true;
  }
}

//
// Arguments    : void
// Return Type  : AsyncBuffer
//
AsyncBuffer::AsyncBuffer()
{
  this->matlabCodegenIsDeleted = true;
}

//
// Arguments    : void
// Return Type  : void
//
AsyncBuffer::~AsyncBuffer()
{
  this->matlabCodegenDestructor();
}

//
// Arguments    : float out_data[]
//                int *out_size
// Return Type  : void
//
void AsyncBuffer::read(float out_data[], int *out_size)
{
  array<float, 1U> out;
  array<int, 2U> readIdx;
  array<int, 2U> y;
  int y_data[16001];
  int b_qY;
  int c;
  int c_qY;
  int d_qY;
  int n;
  int qY;
  int rPtr;
  int wPtr_tmp;
  int yk;
  wPtr_tmp = this->pBuffer.WritePointer;
  qY = 0;
  b_qY = 0;
  n = this->pBuffer.ReadPointer;
  if (n > 2147483646) {
    rPtr = MAX_int32_T;
  } else {
    rPtr = n + 1;
  }
  if (rPtr > 16001) {
    rPtr = 1;
  }
  if (rPtr < -2147468448) {
    c_qY = MIN_int32_T;
    d_qY = MIN_int32_T;
  } else {
    c_qY = rPtr - 15200;
    d_qY = rPtr - 15200;
  }
  c = d_qY + 15999;
  if (c_qY < 1) {
    int k;
    n = 1 - c_qY;
    y_data[0] = c_qY + 16001;
    yk = c_qY + 16001;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    y.set_size(1, d_qY + 15999);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    readIdx.set_size(1, (y.size(1) - c_qY) + 1);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y_data[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[(yk - c_qY) + 1] = y[yk];
    }
    if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= d_qY + 15999)) {
      if ((d_qY + 15999 >= 0) && (wPtr_tmp < d_qY - 2147467648)) {
        c_qY = MAX_int32_T;
      } else if ((d_qY + 15999 < 0) && (wPtr_tmp > d_qY - 2147467649)) {
        c_qY = MIN_int32_T;
      } else {
        c_qY = (d_qY - wPtr_tmp) + 15999;
      }
      if (c_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = c_qY + 1;
      }
    } else if (wPtr_tmp < rPtr) {
      if (c_qY + 16001 < -2147467646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY = -c_qY;
      }
      if (c_qY > 2147483646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY++;
      }
      if ((c_qY < 0) && (wPtr_tmp < MIN_int32_T - c_qY)) {
        b_qY = MIN_int32_T;
      } else if ((c_qY > 0) && (wPtr_tmp > MAX_int32_T - c_qY)) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = c_qY + wPtr_tmp;
      }
    } else if (wPtr_tmp > c_qY + 16001) {
      if ((wPtr_tmp >= 0) && (c_qY + 16001 < wPtr_tmp - MAX_int32_T)) {
        c_qY = MAX_int32_T;
      } else if ((wPtr_tmp < 0) && (c_qY + 16001 > wPtr_tmp - MIN_int32_T)) {
        c_qY = MIN_int32_T;
      } else {
        c_qY = (wPtr_tmp - c_qY) - 16001;
      }
      if (c_qY > 2147483646) {
        b_qY = MAX_int32_T;
      } else {
        b_qY = c_qY + 1;
      }
    }
  } else if (d_qY + 15999 > 16001) {
    int k;
    c = d_qY - 2;
    n = 16002 - c_qY;
    y_data[0] = c_qY;
    yk = c_qY;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
    y.set_size(1, d_qY - 2);
    y[0] = 1;
    yk = 1;
    for (k = 2; k <= c; k++) {
      yk++;
      y[k - 1] = yk;
    }
    readIdx.set_size(1, (y.size(1) - c_qY) + 16002);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y_data[yk];
    }
    n = y.size(1);
    for (yk = 0; yk < n; yk++) {
      readIdx[(yk - c_qY) + 16002] = y[yk];
    }
    if (rPtr <= wPtr_tmp) {
      if (wPtr_tmp < -2147467646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY = 16001 - wPtr_tmp;
      }
      if (c_qY > 2147483646) {
        c_qY = MAX_int32_T;
      } else {
        c_qY++;
      }
      if ((c_qY < 0) && (d_qY - 2 < MIN_int32_T - c_qY)) {
        qY = MIN_int32_T;
      } else if ((c_qY > 0) && (d_qY - 2 > MAX_int32_T - c_qY)) {
        qY = MAX_int32_T;
      } else {
        qY = (c_qY + d_qY) - 2;
      }
    } else if (wPtr_tmp <= d_qY - 2) {
      if (wPtr_tmp < d_qY + MAX_int32_T) {
        c_qY = MAX_int32_T;
      } else {
        c_qY = (d_qY - wPtr_tmp) - 2;
      }
      if (c_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = c_qY + 1;
      }
    } else if ((c_qY < wPtr_tmp) && (wPtr_tmp < rPtr)) {
      b_qY = (wPtr_tmp - c_qY) + 1;
    }
  } else {
    if (d_qY + 15999 < c_qY) {
      n = 0;
    } else {
      n = (d_qY - c_qY) + 16000;
    }
    if (n > 0) {
      y_data[0] = c_qY;
      yk = c_qY;
      for (int k{2}; k <= n; k++) {
        yk++;
        y_data[k - 1] = yk;
      }
    }
    readIdx.set_size(1, n);
    for (yk = 0; yk < n; yk++) {
      readIdx[yk] = y_data[yk];
    }
    if ((rPtr <= wPtr_tmp) && (wPtr_tmp <= d_qY + 15999)) {
      if ((d_qY + 15999 >= 0) && (wPtr_tmp < d_qY - 2147467648)) {
        c_qY = MAX_int32_T;
      } else if ((d_qY + 15999 < 0) && (wPtr_tmp > d_qY - 2147467649)) {
        c_qY = MIN_int32_T;
      } else {
        c_qY = (d_qY - wPtr_tmp) + 15999;
      }
      if (c_qY > 2147483646) {
        qY = MAX_int32_T;
      } else {
        qY = c_qY + 1;
      }
    } else if ((c_qY <= wPtr_tmp) && (wPtr_tmp < rPtr)) {
      b_qY = (wPtr_tmp - c_qY) + 1;
    }
  }
  out.set_size(readIdx.size(1));
  n = readIdx.size(1);
  for (yk = 0; yk < n; yk++) {
    out[yk] = this->pBuffer.Cache[readIdx[yk] - 1];
  }
  if (qY != 0) {
    if (qY < -2147467647) {
      c_qY = MAX_int32_T;
    } else {
      c_qY = 16000 - qY;
    }
    if (c_qY > 2147483646) {
      c_qY = MAX_int32_T;
    } else {
      c_qY++;
    }
    if (c_qY > 16000) {
      c_qY = 1;
    }
    for (yk = 0; yk < qY; yk++) {
      out[(c_qY + yk) - 1] = 0.0F;
    }
  } else if (b_qY != 0) {
    if (b_qY == 16000) {
      out.set_size(16000);
      for (yk = 0; yk < 16000; yk++) {
        out[yk] = 0.0F;
      }
    } else {
      for (yk = 0; yk < b_qY; yk++) {
        out[yk] = 0.0F;
      }
    }
  }
  *out_size = out.size(0);
  n = out.size(0);
  for (yk = 0; yk < n; yk++) {
    out_data[yk] = out[yk];
  }
  if (wPtr_tmp < -2147483647) {
    c_qY = MIN_int32_T;
  } else {
    c_qY = wPtr_tmp - 1;
  }
  n = this->pBuffer.CumulativeUnderrun;
  if ((n < 0) && (qY < MIN_int32_T - n)) {
    d_qY = MIN_int32_T;
  } else if ((n > 0) && (qY > MAX_int32_T - n)) {
    d_qY = MAX_int32_T;
  } else {
    d_qY = n + qY;
  }
  this->pBuffer.CumulativeUnderrun = d_qY;
  if (qY != 0) {
    this->pBuffer.ReadPointer = c_qY;
  } else {
    this->pBuffer.ReadPointer = c;
  }
}

} // namespace dsp
} // namespace coder

//
// File trailer for AsyncBuffer.cpp
//
// [EOF]
//
