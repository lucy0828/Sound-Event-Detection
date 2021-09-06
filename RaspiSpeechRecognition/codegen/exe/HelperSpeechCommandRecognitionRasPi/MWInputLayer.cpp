/* Copyright 2020 The MathWorks, Inc. */

#include "MWInputLayer.hpp"
#include "MWInputLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
// Creating the ImageInputLayer
void MWInputLayer::createInputLayer(MWTargetNetworkImpl* ntwk_impl,
                                    MWTensorBase* m_in,
                                    int /*m_height*/,
                                    int /*m_width*/,
                                    int /*m_channels*/,
                                    int /*m_withAvg*/,
                                    const char* /*avg_file_name*/,
                                    int outbufIdx) {
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWInputLayerImpl(this, ntwk_impl);
}

#elif defined(MW_TARGET_TYPE_TENSORRT) || defined(MW_TARGET_TYPE_ARMMALI)
void MWInputLayer::createInputLayer(MWTargetNetworkImpl* ntwk_impl,
                                    MWTensorBase* m_in,
                                    int  m_height,
                                    int m_width,
                                    int m_channels,
                                    int /*m_withAvg*/,
                                    const char* /*avg_file_name*/,
                                    int outbufIdx) {
    // populate output tensor
    allocateOutputTensor<float>(m_height, m_width, m_channels, m_in->getBatchSize(), 1, NULL);

    assert(m_in->getSequenceLength() == 1);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWInputLayerImpl(this, ntwk_impl);

    assert(getOutputTensor()->getSequenceLength() == 1);
}

#else
void MWInputLayer::createInputLayer(MWTargetNetworkImpl* ntwk_impl,
                                    MWTensorBase* m_in,
                                    int  m_height,
                                    int m_width,
                                    int m_channels,
                                    int m_withAvg,
                                    const char* avg_file_name,
                                    int outbufIdx) {
    
    // This branch is to maintain compatibility with cmdnn
     // populate output tensor
    allocateOutputTensor<float>(m_height, m_width, m_channels, m_in->getBatchSize(), 1, NULL);

    assert(m_in->getSequenceLength() == 1);

    m_impl = new MWInputLayerImpl(this,
                                  ntwk_impl,
                                  m_in->getBatchSize(),
                                  m_height,
                                  m_width,
                                  m_channels,
                                  m_withAvg,
                                  avg_file_name,
                                  outbufIdx);

    assert(getOutputTensor()->getSequenceLength() == 1);
}

#endif

void MWInputLayer::propagateSize() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    resizeOutputTensor(getInputTensor(0)->getHeight(), getInputTensor(0)->getWidth(),
                       getInputTensor(0)->getChannels(), getInputTensor(0)->getBatchSize(),
                       getInputTensor(0)->getSequenceLength());

    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl->propagateSize();
#endif
}
