//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "formatSTFTOutput.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
//
// Arguments    : const ::coder::array<creal32_T, 2U> &S
//                double F_data[]
//                int *F_size
//                const char opts_FreqRange[8]
//                ::coder::array<creal32_T, 2U> &Sout
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace stft {
void formatSTFTOutput(const ::coder::array<creal32_T, 2U> &S, double F_data[],
                      int *F_size, const char opts_FreqRange[8],
                      ::coder::array<creal32_T, 2U> &Sout)
{
  static const char b[8]{'c', 'e', 'n', 't', 'e', 'r', 'e', 'd'};
  static const char b_b[8]{'t', 'w', 'o', 's', 'i', 'd', 'e', 'd'};
  array<creal32_T, 2U> a;
  creal32_T buffer_data[256];
  int ret;
  ret = memcmp(&opts_FreqRange[0], &b[0], 8);
  if (ret == 0) {
    ret = 0;
  } else {
    ret = memcmp(&opts_FreqRange[0], &b_b[0], 8);
    if (ret == 0) {
      ret = 1;
    } else {
      ret = -1;
    }
  }
  switch (ret) {
  case 0: {
    int i;
    a.set_size(512, 98);
    for (i = 0; i < 50176; i++) {
      a[i] = S[i];
    }
    std::memset(&buffer_data[0], 0, 256U * sizeof(creal32_T));
    for (int b_i{0}; b_i < 98; b_i++) {
      int k;
      ret = (b_i << 9) - 1;
      for (k = 0; k < 255; k++) {
        buffer_data[k] = a[(ret + k) + 258];
      }
      for (k = 256; k >= 0; k--) {
        i = ret + k;
        a[i + 256] = a[i + 1];
      }
      for (k = 0; k < 255; k++) {
        a[(ret + k) + 1] = buffer_data[k];
      }
    }
    Sout.set_size(512, 98);
    for (i = 0; i < 50176; i++) {
      Sout[i] = a[i];
    }
    if (std::fmod(static_cast<double>(*F_size), 2.0) == 0.0) {
      double F;
      F = F_data[static_cast<int>(static_cast<double>(*F_size) / 2.0) - 1];
      for (i = 0; i < *F_size; i++) {
        F_data[i] -= F;
      }
    } else {
      double F;
      F = F_data[static_cast<int>((static_cast<double>(*F_size) + 1.0) / 2.0) -
                 1];
      for (i = 0; i < *F_size; i++) {
        F_data[i] -= F;
      }
    }
  } break;
  case 1:
    Sout.set_size(512, 98);
    for (int i{0}; i < 50176; i++) {
      Sout[i] = S[i];
    }
    break;
  default:
    Sout.set_size(257, 98);
    for (int i{0}; i < 98; i++) {
      for (ret = 0; ret < 257; ret++) {
        Sout[ret + Sout.size(0) * i] = S[ret + 512 * i];
      }
    }
    if (*F_size != 257) {
      *F_size = 257;
    }
    break;
  }
}

} // namespace stft
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for formatSTFTOutput.cpp
//
// [EOF]
//
