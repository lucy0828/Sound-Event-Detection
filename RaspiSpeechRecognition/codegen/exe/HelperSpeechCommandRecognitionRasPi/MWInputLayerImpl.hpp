/* Copyright 2020 The MathWorks, Inc. */

#ifndef __INPUT_LAYER_IMPL_HPP
#define __INPUT_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

class MWInputLayerImpl : public MWCNNLayerImpl {

  private:
 
    void predict();
    void propagateSize(){};

    void cleanup() {
    }

  public:
    MWInputLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* ntwk_impl);
    ~MWInputLayerImpl() {
    }
};

#endif
