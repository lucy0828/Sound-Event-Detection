/* Copyright 2020 The MathWorks, Inc. */

#ifndef __SOFTMAX_LAYER_HPP
#define __SOFTMAX_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

// SoftmaxLayer
class MWSoftmaxLayer : public MWCNNLayer {
  public:
    MWSoftmaxLayer() {
    }
    ~MWSoftmaxLayer() {
    }

    void createSoftmaxLayer(MWTargetNetworkImpl*, MWTensorBase*, int);
    void propagateSize();
};

#endif
