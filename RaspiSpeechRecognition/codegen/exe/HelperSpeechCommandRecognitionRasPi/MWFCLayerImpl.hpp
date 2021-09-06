/* Copyright 2020 The MathWorks, Inc. */

#ifndef __FC_LAYER_IMPL_HPP
#define __FC_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include <arm_neon.h>
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// FullyConnectedLayer
class MWFCLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NEFullyConnectedLayer> m_fcLayer;
    arm_compute::Tensor m_fcLayerWgtTensor;
    arm_compute::Tensor m_fcLayerBiasTensor;
    bool isWgtsPadded = false;
    bool isBiasPadded = false;
    float* uznbYLhhKtdvhPWaHJnR;
    float* JxwPQNPACGfmGpNncpCY;

    void loadWeights(const char*, int);
    void loadBias(const char*, int);
    void prepareWeights();
    void propagateSize();
    void predict();
    void cleanup();
    void allocate();
    void deallocate();

  public:
    MWFCLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, const char*, const char*);
    ~MWFCLayerImpl();
};

#endif
