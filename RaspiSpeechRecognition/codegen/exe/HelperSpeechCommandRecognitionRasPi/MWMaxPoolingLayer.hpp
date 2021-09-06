/* Copyright 2020 The MathWorks, Inc. */

#ifndef __MAX_POOLING_LAYER_HPP
#define __MAX_POOLING_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

/**
 * Codegen class for MaxPool layer
 */

// MaxPooling2DLayer
class MWMaxPoolingLayer : public MWCNNLayer {
  public:
    MWMaxPoolingLayer()
        : isGlobalAveragePooling(false) {
    }
    ~MWMaxPoolingLayer() {
    }
    // Create MaxPooling2DLayer with PoolSize = [ PoolH PoolW ]
    //                                Stride = [ StrideH StrideW ]
    //                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]

    template <typename T1, typename T2>    
    void createMaxPoolingLayer(MWTargetNetworkImpl*,
                               MWTensorBase*,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               bool,
                               int,
                               const char*,
                               int,
                               ...);
    void propagateSize();
    
  private:
    int strideH;
    int strideW;

    int poolH;
    int poolW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    bool isGlobalAveragePooling;

    bool hasIndices;
    const char* accelerationMode;
};

#endif
