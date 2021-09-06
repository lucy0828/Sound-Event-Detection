/* Copyright 2020 The MathWorks, Inc. */

// ARMNEON specific implementation of the Custom Layer Base Class
#include "MWCustomLayerForARMNEON.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWACLUtils.hpp"

MWCustomLayerForARMNEON::MWCustomLayerForARMNEON()
    : m_ntwkImpl(NULL) {
    m_isCustomLayer = true;
}

void MWCustomLayerForARMNEON::setupLayer(MWTargetNetworkImpl* targetImpl) {
    m_ntwkImpl = targetImpl;
}

bool MWCustomLayerForARMNEON::isSharedIpArmTensorData(MWTensorBase* aTensor) {
    auto prevLayerOpArmTensor = MWACLUtils::getLayerOpArmTensor(aTensor);
    if (prevLayerOpArmTensor != nullptr && prevLayerOpArmTensor->info()->has_padding()) {
        /* If previous layer has ARM Tensor and if ARM Tensor has padding
         * then we can not share ARM Tensor data to then current layer.
         */
        return false;
    } else {
        return true;
    }
}

void MWCustomLayerForARMNEON::allocate() {
    for (size_t inIdx = 0; inIdx < getNumInputs(); ++inIdx) {
        allocateInputData(inIdx);
    }

    for (size_t outIdx = 0; outIdx < getNumOutputs(); ++outIdx) {
        allocateOutputData(outIdx);
    }
}

void MWCustomLayerForARMNEON::allocateInputData(int inIdx) {
    MWTensorBase* ipTensorBase = getInputTensor(inIdx);
    MWTensor<float>* ipTensor = static_cast<MWTensor<float>*>(ipTensorBase);

    bool shareIpArmTensorData = isSharedIpArmTensorData(ipTensorBase);
    if (!shareIpArmTensorData) {
        // created when ip arm tensor data is not shareable.
        // And this memory used to store the unpadded data.
        // This newly created buffer will be filled in predict call.
        setUnpaddedIpData(ipTensorBase, (float*)calloc(ipTensor->getNumElements(), sizeof(float)));
    } else {
        /* 1. If prevLayerarmTensor is null means either previous layer is handcoded or custom
         * layer. In both these cases we can use input memory directly.
         * 2. Also if previous layer has output ARM Tensor but it has no padding then
         *    we can directly assign input tensor data.
         */
        setUnpaddedIpData(ipTensorBase, (float*)ipTensor->getData());
    }
}

void MWCustomLayerForARMNEON::setUnpaddedIpData(MWTensorBase* aTensor, float* bufPtr) {
    MW_mangled_ipUnPaddedData[aTensor] = bufPtr;
}

float* MWCustomLayerForARMNEON::getUnpaddedIpData(MWTensorBase* aTensor) {
    if (MW_mangled_ipUnPaddedData.size() >= 1) {
        return MW_mangled_ipUnPaddedData[aTensor];
    } else {
        return NULL;
    }
}

void MWCustomLayerForARMNEON::allocateOutputData(int outIdx) {

    MWTensorBase* opTensorBase = getOutputTensor(outIdx);
    MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase);

    int outBufIndex = opTensor->getopBufIndex();
    int inIdx = getInPlaceIndex(outIdx);

    if (outBufIndex < 0) { // without buffer reuse
        if (inIdx != -1) { // Inplace case
            MWTensorBase* ipTensorBase = getInputTensor(inIdx);
            MWTensor<float>* ipTensor = static_cast<MWTensor<float>*>(ipTensorBase);

            float* ipData = ipTensor->getData();
            opTensor->setData(ipData);
        } else { // out of place
            int MW_mangled_numElements = opTensorBase->getNumElements();
            opTensor->setData((float*)calloc(MW_mangled_numElements, sizeof(float)));
        }
    } else {
        /* Buffer reuse can handle both inplace and outplace, based
         * on the outBufIndex.
         */
        float* opBuffer = (float*)(GET_BUFFER(m_ntwkImpl->memBuffer[outBufIndex]));
        opTensor->setData(opBuffer);
    }
}

void MWCustomLayerForARMNEON::prepareUnpaddedIpData() {

    for (size_t inIdx = 0; inIdx < getNumInputs(); inIdx++) {
        MWTensorBase* ipTensorBase = getInputTensor(inIdx);

        float* MW_mangled_inputBuffer = getUnpaddedIpData(ipTensorBase);
        auto prevLayerarmTensor = MWACLUtils::getLayerOpArmTensor(ipTensorBase);

        if (prevLayerarmTensor && prevLayerarmTensor->info()->has_padding()) {
            MWACLUtils::fillTensorToBuffer(MW_mangled_inputBuffer, *prevLayerarmTensor);
        }
    }
}

void MWCustomLayerForARMNEON::reorderData(MWTensorBase* aTensorBase, int bufIndex,
        MWTensorBase::DIMSLABEL sourceLayout[], MWTensorBase::DIMSLABEL targetLayout[], bool isInputReorder) {

    MWTensor<float>* aTensor = static_cast<MWTensor<float>*>(aTensorBase);
    float* ipBuf;
    float* outBuf;

    // Assign input and output data pointers for data reordering.
    if(isInputReorder){ // Custom layer input data reordering
        ipBuf = getUnpaddedIpData(aTensorBase);
        outBuf = m_ntwkImpl->getPermuteBuffer(bufIndex);
    }
    else{// Custom layer output data reordering
        ipBuf = m_ntwkImpl->getPermuteBuffer(bufIndex);
        outBuf = aTensor->getData();
    }

    const int size = 5;
    int sourceDims[size], targetDims[size];
    aTensorBase->getDimsByLayout(sourceLayout, size, sourceDims);
    aTensorBase->getDimsByLayout(targetLayout, size, targetDims);

    int strides[size];
    MWTensorBase::getTransformStrides(sourceLayout, targetLayout, targetDims, size, strides);

    MWACLUtils::doPermutation(ipBuf, outBuf, sourceDims, strides);
}

void MWCustomLayerForARMNEON::deallocate() {
    // deallocate input unpadded data if required.
    for (size_t inIdx = 0; inIdx < getNumInputs(); ++inIdx) {
        MWTensorBase* ipTensorBase = getInputTensor(inIdx);
        bool shareIpArmTensorData = isSharedIpArmTensorData(ipTensorBase);
        if (!shareIpArmTensorData) {
            /* Release memory where we have created extra memory to store unpadded data.
             * This memory created when ip arm tensor data is not shareable.
             */
            float* ipDataBuf = (float*)getUnpaddedIpData(ipTensorBase);
            if (ipDataBuf) {
                free(ipDataBuf);
                setUnpaddedIpData(ipTensorBase, NULL);
            }
        }
    }

    // deallocate output data in "without buffer reuse + out of place" case
    for (size_t outIdx = 0; outIdx < getNumOutputs(); ++outIdx) {
        MWTensorBase* opTensorBase = getOutputTensor(outIdx);
        MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase);
        int inPlaceIdx = getInPlaceIndex(outIdx);

        int opBufIdx = opTensor->getopBufIndex();
        if (opBufIdx < 0 && inPlaceIdx == -1) { // without buffer reuse and out of place case.
            float* opDataBuf = opTensor->getData();
            if (opDataBuf) {
                free(opDataBuf);
            }
            opTensor->setData(NULL);
        }
    }
}

void MWCustomLayerForARMNEON::cleanup() {

    // call layer specific cleanup (this code will be auto-generated)
    this->cleanupLayer();

    // call base layer cleanup
    this->MWCNNLayer::cleanup();
}

MWCustomLayerForARMNEON::~MWCustomLayerForARMNEON() {
}
