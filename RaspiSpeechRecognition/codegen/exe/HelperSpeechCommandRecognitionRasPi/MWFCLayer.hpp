/* Copyright 2020 The MathWorks, Inc. */

#ifndef __FC_LAYER_HPP
#define __FC_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

// FullyConnectedLayer
class MWFCLayer : public MWCNNLayer {
  public:
    MWFCLayer() {
    }
    ~MWFCLayer() {
    }

    void
    createFCLayer(MWTargetNetworkImpl*, MWTensorBase*, int, int, const char*, const char*, int);
    void propagateSize();

  private:
    int numInputFeatures;
    int numOutputFeatures;
};

#endif
