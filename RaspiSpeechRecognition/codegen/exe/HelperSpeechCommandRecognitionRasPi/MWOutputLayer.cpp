/* Copyright 2020 The MathWorks, Inc. */

#include "MWOutputLayer.hpp"
#include "MWOutputLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

// Create ClassificationOutputLayer
// We are doing inference only so LossFunction is not needed.
// This layer would do nothing but point the data to previous layer.
void MWOutputLayer::createOutputLayer(MWTargetNetworkImpl* ntwk_impl,
                                      MWTensorBase* m_in,
                                      int outbufIdx) {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWOutputLayerImpl(this, ntwk_impl);

#else
    setInputTensor(m_in);

    assert(getInputTensor()->isFloat());
    allocateOutputTensor<float>(getInputTensor()->getHeight(), getInputTensor()->getWidth(),
                                getInputTensor()->getChannels(), getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(),
                                static_cast<MWTensor<float>*>(getInputTensor())->getData());

    m_impl = new MWOutputLayerImpl(this, ntwk_impl, outbufIdx);
    return;
#endif
}

void MWOutputLayer::propagateSize() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    resizeOutputTensor(getInputTensor()->getHeight(), getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(), getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());
    m_impl->propagateSize();
#endif
}

void MWOutputLayer::predict() {
    m_impl->predict();
}
