//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: HelperSpeechCommandRecognitionRasPi_internal_types.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

#ifndef HELPERSPEECHCOMMANDRECOGNITIONRASPI_INTERNAL_TYPES_H
#define HELPERSPEECHCOMMANDRECOGNITIONRASPI_INTERNAL_TYPES_H

// Include Files
#include "HelperSpeechCommandRecognitionRasPi_types.h"
#include "rtwtypes.h"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"

// Type Definitions
class commandNet0_0 {
public:
  commandNet0_0();
  void setSize();
  void resetState();
  void setup();
  void predict();
  void cleanup();
  float *getLayerOutput(int layerIndex, int portIndex);
  int getLayerOutputSize(int layerIndex, int portIndex);
  float *getInputDataPointer(int b_index);
  float *getInputDataPointer();
  float *getOutputDataPointer(int b_index);
  float *getOutputDataPointer();
  int getBatchSize();
  ~commandNet0_0();

private:
  void allocate();
  void postsetup();
  void deallocate();
  int numLayers;
  bool isInitialized;
  MWTensorBase *inputTensors[1];
  MWTensorBase *outputTensors[1];
  MWCNNLayer *layers[14];
  MWTargetNetworkImpl *targetImpl;
};

#endif
//
// File trailer for HelperSpeechCommandRecognitionRasPi_internal_types.h
//
// [EOF]
//
