/* Copyright 2020 The MathWorks, Inc. */

#ifndef __OUTPUT_LAYER_HPP
#define __OUTPUT_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

// ClassificationOutputLayer
class MWOutputLayer : public MWCNNLayer {
  public:
    MWOutputLayer() {
    }
    ~MWOutputLayer() {
    }

    void createOutputLayer(MWTargetNetworkImpl*, MWTensorBase*, int);
    void predict();
    void propagateSize();
};

#endif
