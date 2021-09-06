//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: DeepLearningNetwork.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 07-Jul-2021 18:07:43
//

// Include Files
#include "DeepLearningNetwork.h"
#include "HelperSpeechCommandRecognitionRasPi_internal_types.h"
#include "DAHostLib_Network.h"
#include "DAHostLib_rtw.h"
#include "MWCNNLayer.hpp"
#include "MWElementwiseAffineLayer.hpp"
#include "MWFCLayer.hpp"
#include "MWFusedConvReLULayer.hpp"
#include "MWInputLayer.hpp"
#include "MWMaxPoolingLayer.hpp"
#include "MWOutputLayer.hpp"
#include "MWSoftmaxLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensor.hpp"
#include "MWTensorBase.hpp"
#include <string.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::allocate()
{
  this->targetImpl->allocate(2, this->layers, this->numLayers, 0);
  for (int idx{0}; idx < 14; idx++) {
    this->layers[idx]->allocate();
  }
  (static_cast<MWTensor<float> *>(this->inputTensors[0]))
      ->setData(this->layers[0]->getLayerOutput(0));
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::cleanup()
{
  this->deallocate();
  for (int idx{0}; idx < 14; idx++) {
    this->layers[idx]->cleanup();
  }
  if (this->targetImpl) {
    this->targetImpl->cleanup();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::deallocate()
{
  this->targetImpl->deallocate();
  for (int idx{0}; idx < 14; idx++) {
    this->layers[idx]->deallocate();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::postsetup()
{
  this->targetImpl->postSetup();
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::resetState()
{
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::setSize()
{
  for (int idx{0}; idx < 14; idx++) {
    this->layers[idx]->propagateSize();
  }
  this->allocate();
  this->postsetup();
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::setup()
{
  if (this->isInitialized) {
    this->resetState();
  } else {
    this->isInitialized = true;
    this->targetImpl->preSetup();
    (static_cast<MWInputLayer *>(this->layers[0]))
        ->createInputLayer(this->targetImpl, this->inputTensors[0], 98, 50, 1,
                           0, "", 0);
    (static_cast<MWElementwiseAffineLayer *>(this->layers[1]))
        ->createElementwiseAffineLayer(
            this->targetImpl, this->layers[0]->getOutputTensor(0), 1, 1, 1, 1,
            1, 1, false, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_imageinput_scale.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_imageinput_offset.bin",
            -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[2]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[1]->getOutputTensor(0), 3, 3, 1,
            12, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_1_w.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_1_b.bin",
            1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[3]))
        ->createMaxPoolingLayer<float, float>(
            this->targetImpl, this->layers[2]->getOutputTensor(0), 3, 3, 2, 2,
            0, 1, 0, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[4]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[3]->getOutputTensor(0), 3, 3, 12,
            24, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_2_w.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_2_b.bin",
            1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[5]))
        ->createMaxPoolingLayer<float, float>(
            this->targetImpl, this->layers[4]->getOutputTensor(0), 3, 3, 2, 2,
            1, 1, 1, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[6]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[5]->getOutputTensor(0), 3, 3, 24,
            48, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_3_w.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_3_b.bin",
            1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[7]))
        ->createMaxPoolingLayer<float, float>(
            this->targetImpl, this->layers[6]->getOutputTensor(0), 3, 3, 2, 2,
            1, 1, 1, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[8]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[7]->getOutputTensor(0), 3, 3, 48,
            48, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_4_w.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_4_b.bin",
            1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[9]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[8]->getOutputTensor(0), 3, 3, 48,
            48, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_5_w.bin",
            "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
            "cnn_commandNet0_0_conv_5_b.bin",
            0);
    (static_cast<MWMaxPoolingLayer *>(this->layers[10]))
        ->createMaxPoolingLayer<float, float>(
            this->targetImpl, this->layers[9]->getOutputTensor(0), 13, 1, 1, 1,
            0, 0, 0, 0, 0, 0, "FLOAT", 1, 1);
    (static_cast<MWFCLayer *>(this->layers[11]))
        ->createFCLayer(this->targetImpl, this->layers[10]->getOutputTensor(0),
                        336, 12,
                        "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
                        "cnn_commandNet0_0_fc_w.bin",
                        "./codegen/exe/HelperSpeechCommandRecognitionRasPi/"
                        "cnn_commandNet0_0_fc_b.bin",
                        0);
    (static_cast<MWSoftmaxLayer *>(this->layers[12]))
        ->createSoftmaxLayer(this->targetImpl,
                             this->layers[11]->getOutputTensor(0), 1);
    (static_cast<MWOutputLayer *>(this->layers[13]))
        ->createOutputLayer(this->targetImpl,
                            this->layers[12]->getOutputTensor(0), -1);
    this->outputTensors[0] = this->layers[13]->getOutputTensor(0);
    this->setSize();
  }
}

//
// Arguments    : void
// Return Type  : ::commandNet0_0
//
commandNet0_0::commandNet0_0()
{
  this->numLayers = 14;
  this->isInitialized = false;
  this->targetImpl = 0;
  this->layers[0] = new MWInputLayer;
  this->layers[0]->setName("imageinput");
  this->layers[1] = new MWElementwiseAffineLayer;
  this->layers[1]->setName("imageinput_normalization");
  this->layers[1]->setInPlaceIndex(0, 0);
  this->layers[2] = new MWFusedConvReLULayer;
  this->layers[2]->setName("conv_1_relu_1");
  this->layers[3] = new MWMaxPoolingLayer;
  this->layers[3]->setName("maxpool_1");
  this->layers[4] = new MWFusedConvReLULayer;
  this->layers[4]->setName("conv_2_relu_2");
  this->layers[5] = new MWMaxPoolingLayer;
  this->layers[5]->setName("maxpool_2");
  this->layers[6] = new MWFusedConvReLULayer;
  this->layers[6]->setName("conv_3_relu_3");
  this->layers[7] = new MWMaxPoolingLayer;
  this->layers[7]->setName("maxpool_3");
  this->layers[8] = new MWFusedConvReLULayer;
  this->layers[8]->setName("conv_4_relu_4");
  this->layers[9] = new MWFusedConvReLULayer;
  this->layers[9]->setName("conv_5_relu_5");
  this->layers[10] = new MWMaxPoolingLayer;
  this->layers[10]->setName("maxpool_4");
  this->layers[11] = new MWFCLayer;
  this->layers[11]->setName("fc");
  this->layers[12] = new MWSoftmaxLayer;
  this->layers[12]->setName("softmax");
  this->layers[13] = new MWOutputLayer;
  this->layers[13]->setName("classoutput");
  this->layers[13]->setInPlaceIndex(0, 0);
  this->targetImpl = new MWTargetNetworkImpl;
  this->inputTensors[0] = new MWTensor<float>;
  this->inputTensors[0]->setHeight(98);
  this->inputTensors[0]->setWidth(50);
  this->inputTensors[0]->setChannels(1);
  this->inputTensors[0]->setBatchSize(1);
  this->inputTensors[0]->setSequenceLength(1);
}

//
// Arguments    : void
// Return Type  : void
//
commandNet0_0::~commandNet0_0()
{
  this->cleanup();
  for (int idx{0}; idx < 14; idx++) {
    delete this->layers[idx];
  }
  if (this->targetImpl) {
    delete this->targetImpl;
  }
  delete this->inputTensors[0];
}

//
// Arguments    : void
// Return Type  : int
//
int commandNet0_0::getBatchSize()
{
  return this->inputTensors[0]->getBatchSize();
}

//
// Arguments    : void
// Return Type  : float *
//
float *commandNet0_0::getInputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[0]))->getData();
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *commandNet0_0::getInputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[b_index]))
      ->getData();
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : float *
//
float *commandNet0_0::getLayerOutput(int layerIndex, int portIndex)
{
  return this->targetImpl->getLayerOutput(this->layers, layerIndex, portIndex);
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : int
//
int commandNet0_0::getLayerOutputSize(int layerIndex, int portIndex)
{
  return this->layers[layerIndex]
             ->getOutputTensor(portIndex)
             ->getNumElements() *
         sizeof(float);
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *commandNet0_0::getOutputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[b_index]))
      ->getData();
}

//
// Arguments    : void
// Return Type  : float *
//
float *commandNet0_0::getOutputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[0]))->getData();
}

//
// Arguments    : void
// Return Type  : void
//
void commandNet0_0::predict()
{
  for (int idx{0}; idx < 14; idx++) {
    this->layers[idx]->predict();
  }
}

//
// Arguments    : commandNet0_0 *obj
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_setup(commandNet0_0 *obj)
{
  obj->setup();
}

} // namespace coder

//
// File trailer for DeepLearningNetwork.cpp
//
// [EOF]
//
