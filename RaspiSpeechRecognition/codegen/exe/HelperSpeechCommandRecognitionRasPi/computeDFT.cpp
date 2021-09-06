//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDFT.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<float, 2U> &xin
//                ::coder::array<creal32_T, 2U> &Xx
//                double f_data[]
//                int *f_size
// Return Type  : void
//
namespace coder {
void computeDFT(const ::coder::array<float, 2U> &xin,
                ::coder::array<creal32_T, 2U> &Xx, double f_data[], int *f_size)
{
  creal32_T tmp_data[512];
  double w1_data[512];
  float costab_data[257];
  float sintab_data[257];
  float costab1q_data[129];
  int i;
  int k;
  costab1q_data[0] = 1.0F;
  for (k = 0; k < 64; k++) {
    costab1q_data[k + 1] =
        std::cos(0.0122718466F * (static_cast<float>(k) + 1.0F));
  }
  for (k = 0; k < 63; k++) {
    costab1q_data[k + 65] =
        std::sin(0.0122718466F * (128.0F - (static_cast<float>(k) + 65.0F)));
  }
  costab1q_data[128] = 0.0F;
  costab_data[0] = 1.0F;
  sintab_data[0] = 0.0F;
  for (k = 0; k < 128; k++) {
    float costab_tmp;
    float sintab_tmp;
    costab_tmp = costab1q_data[k + 1];
    costab_data[k + 1] = costab_tmp;
    sintab_tmp = -costab1q_data[127 - k];
    sintab_data[k + 1] = sintab_tmp;
    costab_data[k + 129] = sintab_tmp;
    sintab_data[k + 129] = -costab_tmp;
  }
  Xx.set_size(512, 98);
  for (k = 0; k < 98; k++) {
    std::memset(&tmp_data[0], 0, 512U * sizeof(creal32_T));
    internal::fft::FFTImplementationCallback::doHalfLengthRadix2(
        xin, k * 400, tmp_data, costab_data, sintab_data);
    for (i = 0; i < 512; i++) {
      Xx[i + 512 * k] = tmp_data[i];
    }
  }
  for (i = 0; i < 512; i++) {
    w1_data[i] = 0.00390625 * static_cast<double>(i);
  }
  w1_data[256] = 1.0;
  w1_data[511] = 1.99609375;
  *f_size = 512;
  std::copy(&w1_data[0], &w1_data[512], &f_data[0]);
}

} // namespace coder

//
// File trailer for computeDFT.cpp
//
// [EOF]
//
