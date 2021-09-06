/* Copyright 2018 The MathWorks, Inc. */

#ifndef __FUSED_CONV_RELU_LAYER_HPP
#define __FUSED_CONV_RELU_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

/**
  *  Codegen class for Fused Convolution2D-ReLU
**/
class MWFusedConvReLULayer : public MWCNNLayer
{
public:
    MWFusedConvReLULayer();
    ~MWFusedConvReLULayer();
    void createFusedConvReLULayer(MWTargetNetworkImpl* , int,...);
    void propagateSize();

  private:
    int strideH;
    int strideW;
    
    int filterH;
    int filterW;

    int dilationFactorH;
    int dilationFactorW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    int numFilters;
    int numGroups;
    int numChannels;
};

#endif
