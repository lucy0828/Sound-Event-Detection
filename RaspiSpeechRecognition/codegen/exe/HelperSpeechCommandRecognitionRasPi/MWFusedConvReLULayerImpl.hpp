/* Copyright 2018-2020 The MathWorks, Inc. */

#ifndef _MW_FUSED_CONV_LAYER_IMPL
#define _MW_FUSED_CONV_LAYER_IMPL

#include "MWCNNLayerImpl.hpp"
#include <arm_neon.h>
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// Convolution2DWCNNLayer
class MWFusedConvReLULayerImpl : public MWCNNLayerImpl {

  private:
    int BdqURaHPmdnfzvtUvocl;
    int BkwhtPQUCQKchmmimoXs;
    int CCKWXUFWgrbBMjwfpOBN;

    int GIbahSoBBDrvvZduPEqU;
    int GLovsOhUpzOJhKgXUAJY;
    int DGzdAcREJHGXjyRzNjJV;
    int DCdZnqpcBnvXVgEsLBnz;
    int FpguQZSermqZCMRiUfML;
    int FshVHIJMRAhtQirYPlZd;
    int AuqaQHxmPQSyYRemQvyX;
    int BHuHNDGoRwGRouCxeMbw;

    float* uznbYLhhKtdvhPWaHJnR;
    float* JxwPQNPACGfmGpNncpCY;

    bool isWgtsPadding = false;
    bool isBiasPadding = false;

    std::unique_ptr<arm_compute::NEDepthwiseConvolutionLayer>
        m_fusedDepthwiseconvLayer; // used for Depthwise Convolution Layer
    std::unique_ptr<arm_compute::NEConvolutionLayer>
        m_fusedConvLayer; // used for Convolution/1st half of grouped conv
    std::unique_ptr<arm_compute::NEConvolutionLayer>
        m_fusedConvLayerSecondGroup; // used for 2nd half of grouped conv
    /* ReLU activation applied seperately on Convolution kernel output in two cases.
     * 1. Depthwise convolution in ACL v18.05 and v18.08.
     * 2. Grouped convolution output if batchSize>1 upto 19.05.
     */
    std::unique_ptr<arm_compute::NEActivationLayer> m_actLayer;

    arm_compute::Tensor m_fusedConvLayerWgtTensor;
    arm_compute::Tensor m_fusedConvLayerBiasTensor;
    arm_compute::SubTensor*
        m_prevLayer1; // subtensor for current layer input (1st half in grp conv)
    arm_compute::SubTensor*
        m_prevLayer2; // subtensor for current layer input (2nd half in grp conv)
    arm_compute::SubTensor*
        m_curLayer1; // subtensor for current layer output (1st half in grp conv)
    arm_compute::SubTensor*
        m_curLayer2; // subtensor for current layer output (2nd half in grp conv)

    arm_compute::SubTensor*
        m_fusedConvLayerWgtMWTensor; // subtensor for conv weights (1st half in grp conv)
    arm_compute::SubTensor*
        m_fusedConvLayerWgtTensor2; // subtensor for conv weights (2nd half in grp conv)
    arm_compute::SubTensor*
        m_fusedConvLayerBiasMWTensor; // subtensor for conv bias (1st half in grp conv)
    arm_compute::SubTensor*
        m_fusedConvLayerBiasTensor2; // subtensor for conv bias (2nd half in grp conv)
    void propagateSize();

    void predict();
    void cleanup();
    void allocate();
    void deallocate();
    void loadWeights(const char*, int);
    void loadBias(const char*, int);
    
    void configureDepthWiseConvolution();
    void configureGroupedConvolution();

  public:
    MWFusedConvReLULayerImpl(MWCNNLayer*,
                             MWTargetNetworkImpl*,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             int,
                             const char*,
                             const char*);
    ~MWFusedConvReLULayerImpl();
};

#endif
