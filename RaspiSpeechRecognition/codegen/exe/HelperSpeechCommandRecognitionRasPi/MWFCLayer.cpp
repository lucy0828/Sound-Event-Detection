/* Copyright 2020 The MathWorks, Inc. */

#include "MWFCLayer.hpp"
#include "MWFCLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

// Create FullyConnectedLayer with corresponding InputSize and OutputSize.
// This implementation uses SGEMV for m_BatchSize = 1 and SGEMM for others.
void MWFCLayer::createFCLayer(MWTargetNetworkImpl* ntwk_impl,
                              MWTensorBase* m_in,
                              int m_InputSize,
                              int m_OutputSize,
                              const char* m_weights_file,
                              const char* m_bias_file,
                              int outbufIdx) {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    numInputFeatures = m_InputSize;
    numOutputFeatures = m_OutputSize;

    m_impl =
        new MWFCLayerImpl(this, ntwk_impl, m_InputSize, m_OutputSize, m_weights_file, m_bias_file);

#else
    setInputTensor(m_in);
    allocateOutputTensor<float>(1, 1, m_OutputSize, getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(), NULL);

    m_impl =
        new MWFCLayerImpl(this, ntwk_impl, m_InputSize, m_weights_file, m_bias_file, outbufIdx);

    return;
#endif
}

void MWFCLayer::propagateSize() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    resizeOutputTensor(1, 1, numOutputFeatures, getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}
