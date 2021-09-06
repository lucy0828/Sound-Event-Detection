//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: formatSTFTOutput.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef FORMATSTFTOUTPUT_H
#define FORMATSTFTOUTPUT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace stft {
void formatSTFTOutput(const ::coder::array<creal32_T, 2U> &S, double F_data[],
                      int *F_size, const char opts_FreqRange[8],
                      ::coder::array<creal32_T, 2U> &Sout);

}
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for formatSTFTOutput.h
//
// [EOF]
//
