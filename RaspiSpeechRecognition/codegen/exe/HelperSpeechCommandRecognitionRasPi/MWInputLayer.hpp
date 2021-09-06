/* Copyright 2020 The MathWorks, Inc. */

#ifndef __INPUT_LAYER_HPP
#define __INPUT_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

// ImageInputLayer
class MWInputLayer : public MWCNNLayer {
  public:
    MWInputLayer() {
    }
    ~MWInputLayer() {
    }

    void createInputLayer(MWTargetNetworkImpl* ntwk_impl,
                          MWTensorBase* m_in,
                          int,
                          int,
                          int,
                          int,
                          const char* avg_file_name,
                          int);
    void propagateSize();
};

#endif
