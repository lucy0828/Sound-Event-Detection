//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_HelperSpeechCommandRecognitionRasPi_api.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "_coder_HelperSpeechCommandRecognitionRasPi_api.h"
#include "_coder_HelperSpeechCommandRecognitionRasPi_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "HelperSpeechCommandRecognitionRasPi",                // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Definitions
//
// Arguments    : const mxArray *prhs
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi_api(const mxArray *prhs)
{
  static const uint32_T uv[4]{366653167U, 1130706117U, 2822972960U,
                              1242228696U};
  static const char_T *s{"hostIPAddress"};
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  // Check constant function inputs
  i = 4;
  emlrtCheckArrayChecksumR2018b(&st, prhs, false, &i, (const char_T **)&s,
                                &uv[0]);
  // Invoke the target function
  HelperSpeechCommandRecognitionRasPi();
}

//
// Arguments    : void
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  HelperSpeechCommandRecognitionRasPi_xil_terminate();
  HelperSpeechCommandRecognitionRasPi_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void HelperSpeechCommandRecognitionRasPi_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_HelperSpeechCommandRecognitionRasPi_api.cpp
//
// [EOF]
//
