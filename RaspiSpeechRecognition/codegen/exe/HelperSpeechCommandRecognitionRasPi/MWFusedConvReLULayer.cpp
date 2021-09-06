/* Copyright 2018-2020 The MathWorks, Inc. */

#include "MWFusedConvReLULayer.hpp"
#include "MWFusedConvReLULayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"

#include <cstdio>
#include <cassert>
#include <cstdarg>

MWFusedConvReLULayer::MWFusedConvReLULayer()
{
}

MWFusedConvReLULayer::~MWFusedConvReLULayer()
{
}


void MWFusedConvReLULayer::createFusedConvReLULayer(MWTargetNetworkImpl* ntwk_impl, int numInputs, ...)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    va_list args;
    va_start(args, numInputs);

    for(int i = 0; i < numInputs; i++)
    {
        MWTensorBase* inputTensor = va_arg(args, MWTensorBase*);
        setInputTensor(inputTensor, i);
    }
    
    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    filterH = va_arg(args, int);
    filterW  = va_arg(args, int);
    numChannels  = va_arg(args, int);
    numFilters   = va_arg(args, int);
    strideH      = va_arg(args, int);
    strideW      = va_arg(args, int);
    paddingH_T      = va_arg(args, int);
    paddingH_B      = va_arg(args, int);
    paddingW_L      = va_arg(args, int);
    paddingW_R      = va_arg(args, int);
    dilationFactorH = va_arg(args, int);
    dilationFactorW = va_arg(args, int);
    numGroups       = va_arg(args, int);
    const char* m_weights_file = va_arg(args, const char*);
    const char* m_bias_file    = va_arg(args, const char*);
    int outbufIdx         = va_arg(args, int);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWFusedConvReLULayerImpl(this,
                                          ntwk_impl,
                                          filterH,
                                          filterW,
                                          numGroups,
                                          numChannels,
                                          numFilters,
                                          strideH,
                                          strideW,
                                          paddingH_T,
                                          paddingH_B,
                                          paddingW_L,
                                          paddingW_R,
                                          dilationFactorH,
                                          dilationFactorW,
                                          numInputs,
                                          m_weights_file,
                                          m_bias_file);
    
#else
    va_list args;
    va_start(args, numInputs);

    for(int i = 0; i < numInputs; i++)
    {
        MWTensorBase* inputTensor = va_arg(args, MWTensorBase*);
        setInputTensor(inputTensor, i);
    }

    int m_FilterH = va_arg(args, int);
    int m_FilterW  = va_arg(args, int);
    int m_NumChannels  = va_arg(args, int);
    int m_NumFilters   = va_arg(args, int);
    int m_StrideH      = va_arg(args, int);
    int m_StrideW      = va_arg(args, int);
    int m_PaddingH_T      = va_arg(args, int);
    int m_PaddingH_B      = va_arg(args, int);
    int m_PaddingW_L      = va_arg(args, int);
    int m_PaddingW_R      = va_arg(args, int);
    int m_DilationFactorH = va_arg(args, int);
    int m_DilationFactorW = va_arg(args, int);
    int m_NumGroups       = va_arg(args, int);
    const char* m_weights_file = va_arg(args, const char*);
    const char* m_bias_file    = va_arg(args, const char*);
    int outbufIdx         = va_arg(args, int);



    int m_filterH_temp = ((m_FilterH-1)*m_DilationFactorH)+1;
    int m_filterW_temp = ((m_FilterW-1)*m_DilationFactorW)+1;
    int outputH = ((getInputTensor()->getHeight()- m_filterH_temp + m_PaddingH_B + m_PaddingH_T)/m_StrideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- m_filterW_temp + m_PaddingW_L + m_PaddingW_R)/m_StrideW) + 1;

    assert(numInputs == 2 || numInputs == 1);
    if (numInputs == 2)
    {

        assert(getInputTensor(1)->getHeight() == outputH);
        assert(getInputTensor(1)->getWidth() == outputW);
        assert(getInputTensor(1)->getChannels() == m_NumFilters*m_NumGroups);
        assert(getInputTensor(1)->getBatchSize() == getInputTensor(0)->getBatchSize());
        assert(getInputTensor(1)->getSequenceLength() == getInputTensor(0)->getSequenceLength());
    }

    // allocate output tensor
    allocateOutputTensor<float>(outputH, outputW, m_NumFilters*m_NumGroups , getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength(), NULL);
    assert(getOutputTensor()->getSequenceLength() == 1);
    
    m_impl = new MWFusedConvReLULayerImpl(this, ntwk_impl, m_FilterH, m_FilterW, m_NumGroups, m_NumChannels, m_NumFilters, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R, m_DilationFactorH, m_DilationFactorW, m_weights_file, m_bias_file, outbufIdx);
#endif
}

void MWFusedConvReLULayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    int m_filterH_temp = ((filterH-1)*dilationFactorH)+1;
    int m_filterW_temp = ((filterW-1)*dilationFactorW)+1;
    int outputH = ((getInputTensor()->getHeight()- m_filterH_temp + paddingH_B + paddingH_T)/strideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- m_filterW_temp + paddingW_L + paddingW_R)/strideW) + 1;

    assert(getInputTensor()->getSequenceLength() == 1);

    assert(getNumInputs() == 2 || getNumInputs() == 1);
    if (getNumInputs() == 2)
    {

        assert(getInputTensor(1)->getHeight() == outputH);
        assert(getInputTensor(1)->getWidth() == outputW);
        assert(getInputTensor(1)->getChannels() == numFilters*numGroups);
        assert(getInputTensor(1)->getBatchSize() == getInputTensor(0)->getBatchSize());
        assert(getInputTensor(1)->getSequenceLength() == getInputTensor(0)->getSequenceLength());
    }
    
    resizeOutputTensor(outputH,
                       outputW,
                       numFilters*numGroups,
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}
