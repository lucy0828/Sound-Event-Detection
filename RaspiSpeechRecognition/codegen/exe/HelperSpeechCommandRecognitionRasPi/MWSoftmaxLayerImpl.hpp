/* Copyright 2020 The MathWorks, Inc. */

#ifndef __SOFTMAX_LAYER_IMPL_HPP
#define __SOFTMAX_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include <arm_neon.h>
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// SoftmaxLayer
class MWSoftmaxLayerImpl : public MWCNNLayerImpl {
  private:
    std::unique_ptr<arm_compute::NESoftmaxLayer> m_softmaxLayer;
    arm_compute::Tensor inputNHWCArmTensor, tmpSfmaxNHWCArmTensor;
    std::unique_ptr<arm_compute::NEPermute> permuteToNHWC;
    std::unique_ptr<arm_compute::NEPermute> permuteToNCHW;
    bool m_doesChannelwiseSoftmax;

    void propagateSize();
    void predict();
    void allocate();
    void deallocate();


  public:
    MWSoftmaxLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*);
    ~MWSoftmaxLayerImpl();
};

#endif
