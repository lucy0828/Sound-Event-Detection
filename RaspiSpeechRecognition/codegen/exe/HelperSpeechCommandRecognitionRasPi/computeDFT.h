//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeDFT.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
void computeDFT(const ::coder::array<float, 2U> &xin,
                ::coder::array<creal32_T, 2U> &Xx, double f_data[],
                int *f_size);

}

#endif
//
// File trailer for computeDFT.h
//
// [EOF]
//
