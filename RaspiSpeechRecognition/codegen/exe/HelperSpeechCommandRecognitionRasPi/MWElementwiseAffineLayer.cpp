/* Copyright 2018-2020 The MathWorks, Inc. */

#include "MWElementwiseAffineLayer.hpp"
#include "MWElementwiseAffineLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

#include <cstdio>
#include <cassert>

MWElementwiseAffineLayer::MWElementwiseAffineLayer()
{
}

MWElementwiseAffineLayer::~MWElementwiseAffineLayer()
{
}

void MWElementwiseAffineLayer::createElementwiseAffineLayer(MWTargetNetworkImpl* ntwk_impl,
                                          MWTensorBase* m_in,
                                          int m_scaleH,
                                          int m_scaleW,
                                          int m_scaleC,
                                          int m_offsetH,
                                          int m_offsetW,
                                          int m_offsetC,
                                          bool m_isClipped,
                                          int m_lowerBound,
                                          int m_upperBound,
                                          const char* m_scale_file,
                                          const char* m_offset_file,
                                          int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl =  new MWElementwiseAffineLayerImpl(this,
                                               ntwk_impl,
                                               m_scaleH,
                                               m_scaleW,
                                               m_scaleC,
                                               m_offsetH,
                                               m_offsetW,
                                               m_offsetC,
                                               m_isClipped,
                                               m_lowerBound,
                                               m_upperBound,
                                               m_scale_file,
                                               m_offset_file);
    
#else
    setInputTensor(m_in);

    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor<float>(getInputTensor(0)->getHeight(),
                                getInputTensor(0)->getWidth(),
                                numOutputFeatures,
                                getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(),
                                NULL);

    
    m_impl =  new MWElementwiseAffineLayerImpl(this, ntwk_impl, m_scaleH, m_scaleW, m_scaleC, m_offsetH, m_offsetW, m_offsetC, 
                                               m_isClipped, m_lowerBound, m_upperBound, m_scale_file, m_offset_file, outbufIdx);
#endif
}

void MWElementwiseAffineLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    resizeOutputTensor(getInputTensor()->getHeight(),
                       getInputTensor()->getWidth(),
                       getInputTensor()->getChannels(),
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}

