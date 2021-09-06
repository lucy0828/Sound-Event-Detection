/* Copyright 2020 The MathWorks, Inc. */

#include "MWSoftmaxLayer.hpp"
#include "MWSoftmaxLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

// Create SoftmaxLayer
void MWSoftmaxLayer::createSoftmaxLayer(MWTargetNetworkImpl* ntwk_impl,
                                        MWTensorBase* m_in,
                                        int outbufIdx) {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWSoftmaxLayerImpl(this, ntwk_impl);

#else
    setInputTensor(m_in);

    allocateOutputTensor<float>(getInputTensor()->getHeight(), getInputTensor()->getWidth(),
                                getInputTensor()->getChannels(), getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(), NULL);

    m_impl = new MWSoftmaxLayerImpl(this, ntwk_impl, outbufIdx);

    return;
#endif
}

void MWSoftmaxLayer::propagateSize() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    resizeOutputTensor(getInputTensor()->getHeight(), getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(), getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}
