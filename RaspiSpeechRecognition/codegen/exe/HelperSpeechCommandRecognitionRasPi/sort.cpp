//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "sort.h"
#include "sortIdx.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <cmath>
#include <string.h>

// Function Definitions
//
// Arguments    : float x[10]
// Return Type  : void
//
namespace coder {
namespace internal {
void sort(float x[10])
{
  float xwork[10];
  float x4[4];
  int idx[10];
  int iwork[10];
  int i1;
  int i2;
  int i3;
  int ib;
  int k;
  int nNaNs;
  signed char idx4[4];
  signed char perm[4];
  x4[0] = 0.0F;
  idx4[0] = 0;
  x4[1] = 0.0F;
  idx4[1] = 0;
  x4[2] = 0.0F;
  idx4[2] = 0;
  x4[3] = 0.0F;
  idx4[3] = 0;
  for (ib = 0; ib < 10; ib++) {
    idx[ib] = 0;
    xwork[ib] = 0.0F;
  }
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 10; k++) {
    if (std::isnan(x[k])) {
      idx[9 - nNaNs] = k + 1;
      xwork[9 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = static_cast<signed char>(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        float f;
        float f1;
        int i4;
        ib = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        f = x4[i1 - 1];
        f1 = x4[i3 - 1];
        if (f <= f1) {
          f = x4[i2 - 1];
          if (f <= f1) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (f <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          f1 = x4[i4 - 1];
          if (f <= f1) {
            if (x4[i2 - 1] <= f1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        idx[ib - 3] = idx4[perm[0] - 1];
        idx[ib - 2] = idx4[perm[1] - 1];
        idx[ib - 1] = idx4[perm[2] - 1];
        idx[ib] = idx4[perm[3] - 1];
        x[ib - 3] = x4[perm[0] - 1];
        x[ib - 2] = x4[perm[1] - 1];
        x[ib - 1] = x4[perm[2] - 1];
        x[ib] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }
  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    for (k = 0; k < ib; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - ib) + 10;
      idx[i1] = idx4[i2];
      x[i1] = x4[i2];
    }
  }
  ib = (nNaNs >> 1) + 10;
  for (k = 0; k <= ib - 11; k++) {
    i2 = (k - nNaNs) + 10;
    i1 = idx[i2];
    idx[i2] = idx[9 - k];
    idx[9 - k] = i1;
    x[i2] = xwork[9 - k];
    x[9 - k] = xwork[i2];
  }
  if ((nNaNs & 1) != 0) {
    ib -= nNaNs;
    x[ib] = xwork[ib];
  }
  if (10 - nNaNs > 1) {
    for (ib = 0; ib < 10; ib++) {
      iwork[ib] = 0;
    }
    i3 = (10 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        ib = i1 * i3;
        i2 = 10 - (nNaNs + ib);
        if (i2 > i1) {
          merge(idx, x, ib, i1, i2 - i1, iwork, xwork);
        }
      }
      ib = i1 << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        merge(idx, x, k * ib, i1, i1, iwork, xwork);
      }
      i1 = ib;
    }
    if (10 - nNaNs > i1) {
      merge(idx, x, 0, i1, 10 - (nNaNs + i1), iwork, xwork);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
