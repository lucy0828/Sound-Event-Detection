//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "FFTImplementationCallback.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_array.h"
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<float, 2U> &x
//                int xoffInit
//                creal32_T y_data[]
//                const float costab_data[]
//                const float sintab_data[]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace fft {
void FFTImplementationCallback::doHalfLengthRadix2(
    const ::coder::array<float, 2U> &x, int xoffInit, creal32_T y_data[],
    const float costab_data[], const float sintab_data[])
{
  creal32_T reconVar1_data[256];
  creal32_T reconVar2_data[256];
  double d;
  float hcostab_data[129];
  float hsintab_data[129];
  float b_y_im;
  float temp2_im;
  float temp2_re;
  float temp_im;
  float temp_re;
  float y_im;
  int bitrevIndex_data[256];
  int wrapIndex_data[256];
  int i;
  int iheight;
  int iy;
  int ju;
  int k;
  bool tst;
  for (i = 0; i < 128; i++) {
    iy = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[iy];
    hsintab_data[i] = sintab_data[iy];
  }
  ju = 0;
  iy = 1;
  for (i = 0; i < 256; i++) {
    reconVar1_data[i].re = sintab_data[i] + 1.0F;
    reconVar1_data[i].im = -costab_data[i];
    reconVar2_data[i].re = 1.0F - sintab_data[i];
    reconVar2_data[i].im = costab_data[i];
    if (i + 1 != 1) {
      wrapIndex_data[i] = 257 - i;
    } else {
      wrapIndex_data[0] = 1;
    }
    bitrevIndex_data[i] = 0;
  }
  for (k = 0; k < 255; k++) {
    bitrevIndex_data[k] = iy;
    iy = 256;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex_data[255] = iy;
  if ((x.size(0) & 1) == 0) {
    tst = true;
    iy = x.size(0);
  } else if (x.size(0) >= 512) {
    tst = true;
    iy = 512;
  } else {
    tst = false;
    iy = x.size(0) - 1;
  }
  d = static_cast<double>(iy) / 2.0;
  iy = static_cast<int>(d);
  for (i = 0; i < iy; i++) {
    ju = xoffInit + (i << 1);
    k = bitrevIndex_data[i];
    y_data[k - 1].re = x[ju];
    y_data[k - 1].im = x[ju + 1];
  }
  if (!tst) {
    iy = bitrevIndex_data[static_cast<int>(d)] - 1;
    y_data[iy].re = x[xoffInit + (static_cast<int>(d) << 1)];
    y_data[iy].im = 0.0F;
  }
  for (i = 0; i <= 254; i += 2) {
    temp_re = y_data[i + 1].re;
    temp_im = y_data[i + 1].im;
    y_data[i + 1].re = y_data[i].re - y_data[i + 1].re;
    y_data[i + 1].im = y_data[i].im - y_data[i + 1].im;
    y_data[i].re += temp_re;
    y_data[i].im += temp_im;
  }
  iy = 2;
  ju = 4;
  k = 64;
  iheight = 253;
  while (k > 0) {
    int istart;
    int temp_re_tmp;
    for (i = 0; i < iheight; i += ju) {
      temp_re_tmp = i + iy;
      temp_re = y_data[temp_re_tmp].re;
      temp_im = y_data[temp_re_tmp].im;
      y_data[temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    istart = 1;
    for (int j{k}; j < 128; j += k) {
      int ihi;
      temp2_re = hcostab_data[j];
      temp2_im = hsintab_data[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = temp2_re * y_data[temp_re_tmp].re -
                  temp2_im * y_data[temp_re_tmp].im;
        temp_im = temp2_re * y_data[temp_re_tmp].im +
                  temp2_im * y_data[temp_re_tmp].re;
        y_data[temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
  temp2_re = y_data[0].re;
  temp_im = y_data[0].im;
  y_im =
      y_data[0].re * reconVar1_data[0].im + y_data[0].im * reconVar1_data[0].re;
  b_y_im = -y_data[0].im;
  temp_re = temp2_re * reconVar2_data[0].re;
  y_data[0].re = 0.5F * ((y_data[0].re * reconVar1_data[0].re -
                          y_data[0].im * reconVar1_data[0].im) +
                         (temp_re - b_y_im * reconVar2_data[0].im));
  temp2_im = temp2_re * reconVar2_data[0].im;
  y_data[0].im = 0.5F * (y_im + (temp2_im + b_y_im * reconVar2_data[0].re));
  y_data[256].re =
      0.5F *
      ((temp_re - temp_im * reconVar2_data[0].im) +
       (temp2_re * reconVar1_data[0].re - -temp_im * reconVar1_data[0].im));
  y_data[256].im =
      0.5F *
      ((temp2_im + temp_im * reconVar2_data[0].re) +
       (temp2_re * reconVar1_data[0].im + -temp_im * reconVar1_data[0].re));
  for (i = 0; i < 127; i++) {
    temp_re = y_data[i + 1].re;
    temp_im = y_data[i + 1].im;
    iy = wrapIndex_data[i + 1];
    temp2_re = y_data[iy - 1].re;
    temp2_im = y_data[iy - 1].im;
    y_im = y_data[i + 1].re * reconVar1_data[i + 1].im +
           y_data[i + 1].im * reconVar1_data[i + 1].re;
    b_y_im = -y_data[iy - 1].im;
    y_data[i + 1].re = 0.5F * ((y_data[i + 1].re * reconVar1_data[i + 1].re -
                                y_data[i + 1].im * reconVar1_data[i + 1].im) +
                               (temp2_re * reconVar2_data[i + 1].re -
                                b_y_im * reconVar2_data[i + 1].im));
    y_data[i + 1].im = 0.5F * (y_im + (temp2_re * reconVar2_data[i + 1].im +
                                       b_y_im * reconVar2_data[i + 1].re));
    y_data[i + 257].re = 0.5F * ((temp_re * reconVar2_data[i + 1].re -
                                  temp_im * reconVar2_data[i + 1].im) +
                                 (temp2_re * reconVar1_data[i + 1].re -
                                  -temp2_im * reconVar1_data[i + 1].im));
    y_data[i + 257].im = 0.5F * ((temp_re * reconVar2_data[i + 1].im +
                                  temp_im * reconVar2_data[i + 1].re) +
                                 (temp2_re * reconVar1_data[i + 1].im +
                                  -temp2_im * reconVar1_data[i + 1].re));
    y_data[iy - 1].re = 0.5F * ((temp2_re * reconVar1_data[iy - 1].re -
                                 temp2_im * reconVar1_data[iy - 1].im) +
                                (temp_re * reconVar2_data[iy - 1].re -
                                 -temp_im * reconVar2_data[iy - 1].im));
    y_data[iy - 1].im = 0.5F * ((temp2_re * reconVar1_data[iy - 1].im +
                                 temp2_im * reconVar1_data[iy - 1].re) +
                                (temp_re * reconVar2_data[iy - 1].im +
                                 -temp_im * reconVar2_data[iy - 1].re));
    y_data[iy + 255].re = 0.5F * ((temp2_re * reconVar2_data[iy - 1].re -
                                   temp2_im * reconVar2_data[iy - 1].im) +
                                  (temp_re * reconVar1_data[iy - 1].re -
                                   -temp_im * reconVar1_data[iy - 1].im));
    y_data[iy + 255].im = 0.5F * ((temp2_re * reconVar2_data[iy - 1].im +
                                   temp2_im * reconVar2_data[iy - 1].re) +
                                  (temp_re * reconVar1_data[iy - 1].im +
                                   -temp_im * reconVar1_data[iy - 1].re));
  }
  temp2_re = y_data[128].re;
  temp_im = y_data[128].im;
  y_im = y_data[128].re * reconVar1_data[128].im +
         y_data[128].im * reconVar1_data[128].re;
  b_y_im = -y_data[128].im;
  temp_re = temp2_re * reconVar2_data[128].re;
  y_data[128].re = 0.5F * ((y_data[128].re * reconVar1_data[128].re -
                            y_data[128].im * reconVar1_data[128].im) +
                           (temp_re - b_y_im * reconVar2_data[128].im));
  temp2_im = temp2_re * reconVar2_data[128].im;
  y_data[128].im = 0.5F * (y_im + (temp2_im + b_y_im * reconVar2_data[128].re));
  y_data[384].re =
      0.5F *
      ((temp_re - temp_im * reconVar2_data[128].im) +
       (temp2_re * reconVar1_data[128].re - -temp_im * reconVar1_data[128].im));
  y_data[384].im =
      0.5F *
      ((temp2_im + temp_im * reconVar2_data[128].re) +
       (temp2_re * reconVar1_data[128].im + -temp_im * reconVar1_data[128].re));
}

} // namespace fft
} // namespace internal
} // namespace coder

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
