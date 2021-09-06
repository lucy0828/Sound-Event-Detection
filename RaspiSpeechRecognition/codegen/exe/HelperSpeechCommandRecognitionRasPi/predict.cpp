//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: predict.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "predict.h"
#include "DeepLearningNetwork.h"
#include "HelperSpeechCommandRecognitionRasPi_internal_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include <cstring>
#include <string.h>

// Type Definitions
struct cell_wrap_49 {
  float f1[12];
};

struct cell_wrap_48 {
  float f1[4900];
};

// Function Definitions
//
// Arguments    : commandNet0_0 *obj
//                const float varargin_1[4900]
//                float varargout_1[12]
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_predict(commandNet0_0 *obj,
                                 const float varargin_1[4900],
                                 float varargout_1[12])
{
  cell_wrap_48 inMiniBatchGroup;
  cell_wrap_49 outMiniBatchGroup;
  int i;
  for (i = 0; i < 98; i++) {
    for (int i1{0}; i1 < 50; i1++) {
      inMiniBatchGroup.f1[i1 + 50 * i] = varargin_1[i + 98 * i1];
    }
  }
  memcpy(obj->getInputDataPointer(0), inMiniBatchGroup.f1,
         obj->getLayerOutputSize(0, 0));
  obj->predict();
  memcpy(outMiniBatchGroup.f1, obj->getLayerOutput(13, 0),
         obj->getLayerOutputSize(13, 0));
  for (i = 0; i < 12; i++) {
    varargout_1[i] = outMiniBatchGroup.f1[i];
  }
}

} // namespace coder

//
// File trailer for predict.cpp
//
// [EOF]
//
