//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: HelperSpeechCommandRecognitionRasPi_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "HelperSpeechCommandRecognitionRasPi_initialize.h"
#include "HelperSpeechCommandRecognitionRasPi_data.h"
#include "extractSpeechFeatures.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi_initialize()
{
  config_not_empty_init();
  extractSpeechFeatures_init();
  isInitialized_HelperSpeechCommandRecognitionRasPi = true;
}

//
// File trailer for HelperSpeechCommandRecognitionRasPi_initialize.cpp
//
// [EOF]
//
