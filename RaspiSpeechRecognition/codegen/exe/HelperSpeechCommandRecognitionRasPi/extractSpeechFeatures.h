//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: extractSpeechFeatures.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef EXTRACTSPEECHFEATURES_H
#define EXTRACTSPEECHFEATURES_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void config_not_empty_init();

void extractSpeechFeatures(const float x_data[], float featureVector_data[],
                           int featureVector_size[2]);

void extractSpeechFeatures_init();

#endif
//
// File trailer for extractSpeechFeatures.h
//
// [EOF]
//
