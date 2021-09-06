//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_HelperSpeechCommandRecognitionRasPi_mex.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "_coder_HelperSpeechCommandRecognitionRasPi_mex.h"
#include "_coder_HelperSpeechCommandRecognitionRasPi_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  (void)plhs;
  mexAtExit(&HelperSpeechCommandRecognitionRasPi_atexit);
  // Module initialization.
  HelperSpeechCommandRecognitionRasPi_initialize();
  try {
    emlrtShouldCleanupOnError((emlrtCTX *)emlrtRootTLSGlobal, false);
    // Dispatch the entry-point.
    unsafe_HelperSpeechCommandRecognitionRasPi_mexFunction(nlhs, nrhs, prhs);
    // Module termination.
    HelperSpeechCommandRecognitionRasPi_terminate();
  } catch (...) {
    emlrtCleanupOnException((emlrtCTX *)emlrtRootTLSGlobal);
    throw;
  }
}

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2021a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr);
  return emlrtRootTLSGlobal;
}

//
// Arguments    : int32_T nlhs
//                int32_T nrhs
//                const mxArray *prhs[1]
// Return Type  : void
//
void unsafe_HelperSpeechCommandRecognitionRasPi_mexFunction(
    int32_T nlhs, int32_T nrhs, const mxArray *prhs[1])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs < 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooFewInputsConstants", 9, 4, 35,
                        "HelperSpeechCommandRecognitionRasPi", 4, 35,
                        "HelperSpeechCommandRecognitionRasPi", 4, 35,
                        "HelperSpeechCommandRecognitionRasPi");
  }
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        35, "HelperSpeechCommandRecognitionRasPi");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 35,
                        "HelperSpeechCommandRecognitionRasPi");
  }
  // Call the function.
  HelperSpeechCommandRecognitionRasPi_api(prhs[0]);
}

//
// File trailer for _coder_HelperSpeechCommandRecognitionRasPi_mex.cpp
//
// [EOF]
//
