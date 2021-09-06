/* Copyright 2020 The MathWorks, Inc. */

#include "MWCNNLayer.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"

#include <string>
#include <stdexcept>
#include <cstdarg>
#include <cassert>
#include <cstdio>

// Get string value from the macro
#define XSTR(x) #x
#define STR(x) XSTR(x)

MWCNNLayer::MWCNNLayer()
    : m_impl(NULL)
    , m_isCustomLayer(false) {
}

MWCNNLayer::~MWCNNLayer() {
}

void MWCNNLayer::predict() {
    if (m_impl) {
        m_impl->predict();
    }
}

/**
 * everything instantiated during setup() should be cleaned up here
 */
void MWCNNLayer::cleanup() {
    if (m_impl) {
        m_impl->cleanup();
        delete m_impl;
        m_impl = 0;
    }

    for (int idx = 0; idx < getNumOutputs(); idx++) {
        MWTensorBase* op = getOutputTensor(idx);
        delete op;
        op = 0;
        m_output[idx] = 0;
    }

    // free up tensor maps
    m_input.clear();
    m_output.clear();
}



void MWCNNLayer::allocate() {
    if (m_impl) {
#if defined(MW_TARGET_TYPE_ARMNEON)
        // Call to ARM Neon allocateInputData to update right
        // unpadded buffer address to m_unpaddedIpData, input ARM tensors
        // in Hand-coded and ACL layer respectively.
        for (int i = 0; i < getNumInputs(); ++i) {
            m_impl->allocateInputData(i);
        }
#endif
        for (int i = 0; i < getNumOutputs(); ++i) {
            // allocate memory for each output tensor
            if (getOutputTensor(i)->isFloat()) {
                allocateOutputData<float>(i);
            } else {
                assert(getOutputTensor(i)->isInt8());
                allocateOutputData<signed char>(i);
            }
        }
        m_impl->allocate();
    }
}

template <class T>
void MWCNNLayer::allocateOutputData(int i) {
    m_impl->allocateOutputData<T>(i);
}

void MWCNNLayer::deallocate() {
    if (m_impl) {
#if defined(MW_TARGET_TYPE_ARMNEON)
        for (int i = 0; i < getNumInputs(); ++i) {
            m_impl->deallocateInputData(i);
        }
#endif
        // deallocate memory for each output tensor
        for (int i = 0; i < getNumOutputs(); ++i) {
            if (getOutputTensor(i)->isFloat()) {
                deallocateOutputData<float>(i);
            } else {
                assert(getOutputTensor(i)->isInt8());
                deallocateOutputData<signed char>(i);
            }
        }
        m_impl->deallocate();
    }
    resetTensorDataPointers();
}

// remove dangling pointers
void MWCNNLayer::resetTensorDataPointers() {
    for (int i = 0; i < getNumOutputs(); ++i) {
        MWTensorBase* opTensorBase = getOutputTensor(i);

        if (opTensorBase->isFloat()) {
            static_cast<MWTensor<float>*>(opTensorBase)->setData((float*)NULL);
        } else {
            assert(opTensorBase->isInt8());
            static_cast<MWTensor<signed char>*>(opTensorBase)->setData((signed char*)NULL);
        }
    }
}

template <class T>
void MWCNNLayer::deallocateOutputData(int i) {
    MWTensorBase* opTensorBase = getOutputTensor(i);

    bool bufferReuse = opTensorBase->getopBufIndex() >= 0;
    if (!bufferReuse) {
        T* data = static_cast<MWTensor<T>*>(opTensorBase)->getData();
        if (data) {
            m_impl->deallocateOutputData<T>(i);
        }
    }
}

void MWCNNLayer::postSetup() {
    if (m_impl) {
        m_impl->postSetup();
    }
}

void MWCNNLayer::setName(const std::string& n) {
    m_name = n;
    return;
}

MWTensorBase* MWCNNLayer::getInputTensor(int index) {
    std::map<int, MWTensorBase*>::iterator it = m_input.find(index);
    assert(it != m_input.end());
    return it->second;
}

MWTensorBase* MWCNNLayer::getOutputTensor(size_t index) {
    std::map<int, MWTensorBase*>::iterator it = m_output.find(static_cast<const int>(index));
    assert(it != m_output.end());
    return it->second;
}

void MWCNNLayer::setInputTensor(MWTensorBase* other, int index) {
    m_input[index] = other;
}

int MWCNNLayer::getHeight(int index) {
    return getOutputTensor(index)->getHeight();
}

int MWCNNLayer::getBatchSize() {
    // return batch size from the output tensor
    return getOutputTensor(0)->getBatchSize();
}

int MWCNNLayer::getWidth(int index) {
    return getOutputTensor(index)->getWidth();
}

int MWCNNLayer::getNumInputFeatures(int index) {
    return getInputTensor(index)->getChannels();
}

int MWCNNLayer::getNumOutputFeatures(int index) {
    return getOutputTensor(index)->getChannels();
}

float* MWCNNLayer::getLayerOutput(int index) {
    // assumes layer output is float type
    return static_cast<MWTensor<float>*>(getOutputTensor(index))->getData();
}

void MWCNNLayer::resizeOutputTensor(int numHeight,
                                    int numWidth,
                                    int numChannels,
                                    int batchSize,
                                    int sequenceLength,
                                    int index) {
    std::map<int, MWTensorBase*>::iterator it = m_output.find(index);
    assert(it != m_output.end());
    it->second->setHeight(numHeight);
    it->second->setWidth(numWidth);
    it->second->setChannels(numChannels);
    it->second->setBatchSize(batchSize);
    it->second->setSequenceLength(sequenceLength);
}

void MWCNNLayer::setupTensors(int numInputs, int numOutputs, ...) {

    // initialize the variable argument list
    va_list args;
    va_start(args, numOutputs);

    // set all the input tensors
    for (int iTensor = 0; iTensor < numInputs; iTensor++) {
        MWTensorBase* inputTensor = va_arg(args, MWTensorBase*);
        setInputTensor(inputTensor, iTensor);
    }

    // set buffer index for all the output tensors
    for (int oTensor = 0; oTensor < numOutputs; oTensor++) {
        // allocate the tensor
        allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL, oTensor);

        int outbufIdx = va_arg(args, int);
        getOutputTensor(oTensor)->setopBufIndex(outbufIdx);
    }

    va_end(args);
}

// static util functions
// open filename
// if file is not found, look in current directory
FILE* MWCNNLayer::openBinaryFile(const char* fileName) {
    FILE* fp = fopen(fileName, "rb");
    if (!fp) {
        std::string fileS(fileName);
        std::string codegenFolder;

        /* Code to extract the directory path */
        size_t fNamePos = fileS.find_last_of("/\\");

        if (fNamePos != std::string::npos) {
            codegenFolder = fileS.substr(0, fNamePos);
        } else {
            /* Default path when there is no directory*/
            codegenFolder = std::string(".");
        }

        size_t pos = 0;
#ifdef MW_DL_DATA_PATH
        fileS = MWCNNLayer::getFilePath(fileS);
#else
#if defined(_WIN32) || defined(_WIN64)

        char delim_unix[] = "/";
        char delim_win[] = "\\";

        while (((pos = fileS.find(delim_unix)) != std::string::npos) ||
               ((pos = fileS.find(delim_win)) != std::string::npos))
#else
        char delim_unix[] = "/";

        while ((pos = fileS.find(delim_unix)) != std::string::npos)
#endif
        {
            if (pos == (fileS.size() - 1)) {
                fileS = "";
                break;
            }
            fileS = fileS.substr(pos + 1);
        }
#endif

        if (!fileS.empty()) {
            fp = fopen(fileS.c_str(), "rb");
        }

        if (!fp) {
            std::string errmsg = std::string("Unable to find the ") + fileS +
                                 std::string(" binary file in ") + codegenFolder +
                                 std::string(" .");
            throw std::runtime_error(errmsg.c_str());
        }
    }

    return fp;
}

std::runtime_error MWCNNLayer::getFileOpenError(const char* filename) {
    const std::string message = std::string("Error! Unable to open file ") + std::string(filename);
    return std::runtime_error(message);
}

std::string MWCNNLayer::getFilePath(std::string fileS) {
    char* usrDataPath = NULL;
    std::string path;

    // Get file path from user environment
    usrDataPath = getenv("USER_DL_DATA_PATH");

    if (usrDataPath != NULL) {
        path = usrDataPath;
    } else {
        // Get file path from macro
        path = STR(MW_DL_DATA_PATH);
    }

    // Find name of file
    size_t fNamePos = fileS.find_last_of("/\\");

    if (fNamePos != std::string::npos) {
        std::string fileN(fileS.substr(fNamePos));
        fileS = path + fileN;
    } else {
        fileS = path + fileS;
    }

    return fileS;
}
